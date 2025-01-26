#include<bits/stdc++.h>
#include<graphics.h>
#include <easyx.h>
#include <WinSock2.h>
#include<windows.h>
#include <iostream>
#include<fstream>
#include<cstring>
#pragma comment(lib, "ws2_32.lib")
using namespace std;

const char* host = "api.seniverse.com";
const char* key = "SmKNAkNDNgy0VQHrh";
const char* language = "zh-Hans";
char _url[100] = { 0 };

char* generateUrl(const char* key, const char* location, const char* language) {
	sprintf(_url, "GET /v3/weather/now.json?key=%s&location=%s&language=%s&unit=c\r\n\r\n",
	        key, location, language);
	return _url;
}

SOCKET connetToHost(const char* host, unsigned int port) {
	//connet to the server

	WSADATA data;
	WSAStartup(MAKEWORD(2, 2), &data);

	//1.create socket
	SOCKET fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == INVALID_SOCKET) {
		printf("socket failed, %d\n", WSAGetLastError());
		return INVALID_SOCKET;
	}

	//2.bind
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	//method 1, at main use truly ip
	//addr.sin_addr.S_un.S_addr = inet_addr(host);
	//method 2, use dns to get ip by name
	hostent *hostent =  gethostbyname(host);
	if (hostent)
		memcpy(&addr.sin_addr, hostent->h_addr_list[0], sizeof(addr.sin_addr));
	else {
		printf("dns failed\n");
		return INVALID_SOCKET;
	}

	//3.connet
	//in cpp, usually return 0 is right
	if (connect(fd, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		printf("connect failed %d\n", WSAGetLastError());
		return INVALID_SOCKET;
	}
	return fd;
}

string weatherget(string cityn) { // codeing:ansi
	SOCKET fd = connetToHost("116.62.81.138", 80);
	if (fd != INVALID_SOCKET)
		printf("connect successfully\n");

	char* url = generateUrl(key, cityn.c_str(), language);
	if (send(fd, url, strlen(url), 0) <= 0)
		printf("send failed %d\n", WSAGetLastError());
	else {
		char buff[BUFSIZ] = {0};
		if (recv(fd, buff, BUFSIZ, 0) <= 0){
			printf("recv failed %d\n", WSAGetLastError());
			return "*";
		}
		else {
			string u8 = buff;
			string ansi = utf8_to_ansi(u8);
			cout<<ansi<<endl;
			//save in file
			FILE* fp = fopen("weather.json", "w");
			if (!fp){
				perror("create file failed\n");
				closesocket(fd);
				return "*";
			}
			else{
				fwrite(buff, sizeof(char), strlen(buff), fp);
			}
			fclose(fp);
			closesocket(fd);
			return ansi;
		}
	}

	closesocket(fd);

	return "*";
}

struct WEATHER{
	string str[9];
	int num[9];
	// {"results":[{"location":{"id":"WS10730EM8EV","name":"??","country":"CN", \
	"path":"??,??,??,??","timezone":"Asia/Shanghai","timezone_offset":"+08:00"} \
	,"now":{"text":"?","code":"0","temperature":"20"},"last_update":"2025-01-21 \
	T11:14:13+08:00"}]}
	int saveweather(string s,bool note = 0){
		if(s.find("You have exceeded your usage quota.")!=string::npos){
			cout<<"API error\n";
			return 1;
		}
		if(s.find("Wrong parameters")!=string::npos){
			cout<<"API error\n";
			return 1;
		}
		if(s.find("The location can not be found.")!=string::npos){
			cout<<"API error\n";
			return 1;
		}
		string fs[10] = {
		"name","country","path","timezone"
		,"timezone_offset","text","code",
		"temperature","last_update","}]}"};
		bool isint[9] = {0,0,0,0,0,0,1,1,0};
		int pys[9] = {7,10,7,11,18,7,7,14,14};
		int pye[9] = {3,3,3,3,11,3,3,4,1};
		for(int i = 0;i<9;i++){
			int p1 = s.find(fs[i]);
			int p2 = s.find(fs[i+1]);
			int st = p1+pys[i],ed = p2-pye[i];
			int l = ed-st;
			string cut = s.substr(st,l);
			if(isint[i]){
				num[i] = stoi(cut);
			}
			else{
				str[i] = cut;
			}
			if(note)cout<<"cut i:"<<i<<" str:"<<cut<<endl;
		}
		return 0;
	}
};

vector<string>city;
vector<string>citycn;
string ccity;
void readcity(){
	ifstream ifs("weather\\city.txt");
	string s;
	while(ifs>>s && s!="STOP"){
		city.push_back(s);
		ifs>>s;
		citycn.push_back(s);
	}
	cout<<"read "<<city.size()<<" city.\n";
	ifs.close();
	ifstream sett("weather\\set.ini");
	sett>>ccity;
	cout<<"ccity is "<<ccity<<endl;
	sett.close();
}
int choosecity(int d = 0){
	setfillcolor(BLACK);
	setlinecolor(YELLOW);
	for(int i = 0;i<6;i++){
		for(int j = 0;j<8;j++){
			if(i==5&&(j==6||j==7)) continue;
			fillrectangle(100*i,50*j,100+100*i,50+50*j);
			if(i*8+j+d*46<citycn.size()){
				string s = citycn[i*8+j+d*46];
				int wd = 98/(s.size());
				settextstyle(wd*2,wd,"");
				int sty = 50*j+(50/2-wd);
				outtextxy(100*i+1,50*j+1,s.c_str());
			}
		}
	}
	settextstyle(24,12,"");
	outtextxy(100*5+2,50*6+2,"下一页");
	outtextxy(100*5+2,50*7+2,"上一页");
	while(1){
		MOUSEMSG msg;
		msg = GetMouseMsg();
		if(msg.uMsg == WM_LBUTTONDOWN){
			int dx = msg.x/100,dy = msg.y/50;
			int p = dx*8+dy;
			cout<<"choose city successfully p:"<<p<<endl;
			if(p==46) return choosecity(d+1)+46;
			if(p==47) return choosecity(d-1)-46;
			return p;
		}
	}
}
int printweather(WEATHER w){
	cls();//cppgraphics.cpp
	IMAGE icon;
	string fn = "weather\\"+w.str[5]+".png";
	loadimage(&icon,fn.c_str(),100,100);
    putimage(0,0,&icon);
	settextcolor(WHITE);
	settextstyle(64,32,"");
	outtextxy(100,0,w.str[0].c_str());
	settextstyle(30,15,"");
	outtextxy(100,65,w.str[2].c_str());
	settextstyle(24,12,"");
	string t = w.str[5]+" "+to_string(w.num[7])+"℃";
	outtextxy(0,100,t.c_str());
	settextstyle(24,12,"");
	outtextxy(0,125,w.str[8].c_str());
	IMAGE img;
    loadimage(&img, "weather\\xuanze.png");
    putimage(0,300,&img);
	IMAGE img1;
    loadimage(&img1, "weather\\exit.bmp",100,100);
    putimage(100,300,&img1);
	IMAGE img2;
    loadimage(&img2, "weather\\moren.png");
    putimage(200,300,&img2);
}
int mainweather(){
	readcity();
	string s = weatherget(ccity);
	WEATHER sz;
	int r = sz.saveweather(s,1);
	if(r==0) printweather(sz);
	else{
		cout<<"cannot print weather!\n";
		return 1;
	}
	int p = 0;
	while(1){
		MOUSEMSG msg;
		msg = GetMouseMsg();
		if(msg.uMsg == WM_LBUTTONDOWN){
			if(msg.y>=300){
				if(msg.x<100){
					p = choosecity();
					if(p<0 || p>=city.size()){
						cout<<"error choose city!\n";
						p = 0;
					}
					WEATHER t;
					s = weatherget(city[p]);
					int r = t.saveweather(s,1);
					if(r==0) printweather(t);
					else{
						cout<<"cannot print weather!\n";
						return 1;
					}
				}
				else if(msg.x>=100&&msg.x<=200){
					return 0;
				}
				else if(msg.x>=200&&msg.x<=300){
					ofstream ofs("weather\\set.ini");
					ofs.clear();
					ofs<<city[p];
					ofs.close();
					cout<<"reset ccity:"<<city[p]<<endl;
				}
			}
		}
	}
	//int p = choosecity();
	return 0;
}
