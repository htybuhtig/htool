#include<bits/stdc++.h>
#include<graphics.h>
#include <easyx.h>
#include<vector>
#include<fstream>
#include"cppgraphics.cpp"
#pragma once
using namespace std;
//recaptcha.cpp
struct CAPTCHA{
	string s;
	vector<int>v;
};
CAPTCHA cha[15];
int drawcaptcha(int n){
	cls();
	
	setlinecolor(WHITE);
	string fn = "recaptcha\\1 ("+to_string(n)+").jpg";
	IMAGE img;
    loadimage(&img,fn.c_str(), 400, 400);
    putimage(0,0,&img);
	IMAGE img1;
    loadimage(&img1,"recaptcha\\microsoft.jpg");
    putimage(400,300-24,&img1);

	line(0,0,0,400);
	line(100,0,100,400);
	line(200,0,200,400);
	line(300,0,300,400);
	line(400,0,400,400);

	line(0,0,400,0);
	line(0,100,400,100);
	line(0,200,400,200);
	line(0,300,400,300);
	line(0,400,400,400);

	settextcolor(WHITE);
	settextstyle(24,12,"");
	outtextxy(401,25, "请选择所有的");
	settextcolor(YELLOW);
	outtextxy(401,50, cha[n].s.c_str());
	settextstyle(20,10,"");
	outtextxy(401,0, "帮助我们战胜机器人");
}
vector<int> getchoosecha(){
	vector<int> ans;
	while(1){
		MOUSEMSG msg;
		msg = GetMouseMsg();
		if(msg.uMsg == WM_LBUTTONDOWN){
			if(msg.x<=400){
				int dx=msg.x/100;
				int dy=msg.y/100;
				int p = dy*4+dx+1;
				bool f = 0;
				for(auto i : ans){
					if(i==p) f = 1;
				}
				if(f==1){
					cout<<"choosed p:"<<p<<endl;
				}
				else{
					ans.push_back(p);
					cout<<"choose p:"<<p<<endl;
					setlinecolor(YELLOW);
					rectangle(dx*100,dy*100,dx*100+100,dy*100+100);
					setlinecolor(WHITE);
				}
			}
			if(msg.x>400&&msg.x<=500&&msg.y>=300&&msg.y<400){
				return ans;
			}
		}
	}
}
int getfen(vector<int> a,vector<int> b){
	int ans = 0;
	for(auto i : a){
		bool f = 0;
		for(auto j : b){
			if(j==i) f = 1;
		}
		ans+=((f==1)?8:(-10));
	}
	for(auto i : b){
		bool f = 0;
		for(auto j : a){
			if(j==i) f = 1;
		}
		ans+=((f==1)?8:(-10));
	}
	return ans;
}
int photorecaptcha(int n){
	if(n==0) return 1;
	int cnt = 0,len;
	int g[101];
	memset(g,0,sizeof g);
	queue<int> q;
	ifstream ifs("recaptcha\\recaptcha.ini");
	ifs>>len;
	cout<<"len:"<<len<<endl;
	for(int i = 1;i<=n;i++){
		int t = rand()%len;
		while(g[t]!=0){
			t=rand()%len;
		}
		g[t]=1;
		q.push(t+1);
		cout<<"push to q:"<<t+1<<endl;
	}
	for(int i = 1;i<=len;i++){
		ifs>>cha[i].s;
		int t;
		cout<<"i:"<<i<<" s:"<<cha[i].s<<" ";
		while(ifs>>t && t!=0){
			cha[i].v.push_back(t);
			cout<<t<<" ";
		}
		cout<<endl;
	}
	IMAGE ok;
    loadimage(&ok,"recaptcha\\ok.jpg", 100, 100);
    putimage(0,0,&ok);
	while(!q.empty()){
		int i = q.front();
		q.pop();
		cout<<"i:"<<i<<endl;
		drawcaptcha(i);
    	putimage(400,300,&ok);
		vector<int> t = getchoosecha();
		int fen = getfen(t,cha[i].v);
		cnt+=fen;
		cout<<"fen is:"<<fen<<" cnt is:"<<cnt<<endl;
	}
	cls();
	settextcolor(WHITE);
	settextstyle(24,12,"");
	outtextxy(0,0, "请稍候，正在验证你是否是人类");
	Sleep(500);
	string s = ((cnt>50)?"你是人类":"你不是人类");
	int res = ((cnt>50)?1:0);
	outtextxy(0,100,s.c_str());
	if(res==1){
		IMAGE ok1;
	    loadimage(&ok1,"recaptcha\\end.png");
	    putimage(600-278,50,&ok1);
	}
	Sleep(1500);
	return res;
}
string ch = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ@#$%";
string chyb = "123456789ABCDEFGHIJKLMNPQRSTUVWXYZ@#$%";
string chkey = "QWERTYUIOPASDFGHJKL@ZXCVBNM#$%1234567890";
int drawkeys(){
	setfillcolor(BLACK);
	setlinecolor(YELLOW);
	settextcolor(WHITE);
	settextstyle(24,12,"");
	for(int i = 0;i<4;i++){
		for(int j = 0;j<10;j++){
			int p = j+i*10;
			int dy = 200+i*50;
			int dx = j*50;
			fillrectangle(dx,dy,dx+50,dy+50);
			outtextxy(dx+3,dy+5,chkey[p]);
		}
	}
	fillrectangle(0,150,600,200);
	fillrectangle(500,200,600,300);
	outtextxy(503,205,"确认");
	fillrectangle(500,300,600,400);
	outtextxy(503,305,"DEL");
}
string inputstr(){
	setfillcolor(BLACK);
	setlinecolor(YELLOW);
	settextcolor(WHITE);
	settextstyle(24,12,"");
	string s;
	while(1){
		MOUSEMSG msg;
		msg = GetMouseMsg();
		if(msg.uMsg == WM_LBUTTONDOWN){
			if(msg.y>200){
				if(msg.x<500){
					int dx = msg.x/50;
					int dy = (msg.y-200)/50;
					int p = dy*10+dx;
					char c = chkey[p];
					s+=c;
				}
				else{
					if(msg.y<300){
						break;
					}
					else{
						if(s.size()>0) s.erase(s.size()-1);
					}
				}
			}
			fillrectangle(0,150,600,200);
			outtextxy(3,152,s.c_str());
		}
	}
	return s;
}
int drawcha(string s){
	fillrectangle(0,0,200,100);
	settextstyle(rand()%16+18,rand()%8+16,"B");
	settextcolor(rand()%2==0 ? YELLOW : WHITE);
	outtextxy(rand()%10+5,rand()%80+5,s[0]);
	settextstyle(rand()%16+18,rand()%8+16,"B");
	settextcolor(rand()%2==0 ? YELLOW : WHITE);
	outtextxy(rand()%10+55,rand()%80+5,s[1]);
	settextstyle(rand()%16+18,rand()%8+16,"B");
	settextcolor(rand()%2==0 ? YELLOW : WHITE);
	outtextxy(rand()%10+105,rand()%80+5,s[2]);
	settextstyle(rand()%16+18,rand()%8+16,"B");
	settextcolor(rand()%2==0 ? YELLOW : WHITE);
	outtextxy(rand()%10+155,rand()%80+5,s[3]);
	for(int i = 0;i<20;i++){
		setlinecolor(rand()%2==0 ? YELLOW : WHITE);
		line(rand()%200,rand()%100,rand()%200,rand()%100);
	}
	for(int i = 0;i<6;i++){
		setlinecolor(rand()%2==0 ? YELLOW : WHITE);
		circle(rand()%100+25,rand()%50+24,rand()%25);
		rectangle(rand()%200,rand()%100,rand()%200,rand()%100);
	}
	setfillcolor(BLACK);
	setlinecolor(YELLOW);
	rectangle(0,0,200,100);
	settextcolor(WHITE);
}
int charrecaptcha(){
	cls();
	string s;
	for(int i = 0;i<4;i++){
		s += chyb[rand()%chyb.size()];
	}
	drawkeys();
	drawcha(s);
	string t = inputstr();
	cout<<"s is:"<<s<<endl;
	cout<<"t is:"<<t<<endl;
	return (t==s);
}
int mainrecaptcha(int a = 0,int b = 8){
	srand(time(0));
	int r1 = 1;
	if(a!=0) r1=photorecaptcha(a);
	int r2 = 0;
	for(int i = 0;i<b;i++){
		r2 += charrecaptcha();
		cout<<"i:"<<i<<" r:"<<r2<<endl;
	}
	cout<<"r1:"<<r1<<" r2:"<<r2<<endl;
	if(r1+r2==1+b){
		cls();
		IMAGE ok1;
	    loadimage(&ok1,"recaptcha\\end.png");
	    putimage(250,100,&ok1);
	}
	Sleep(1000);
	return (r1+r2)==(b+1);
}
