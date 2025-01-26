#include<bits/stdc++.h>
#include<graphics.h>
#include <easyx.h>
#include"cppgraphics.cpp"
#include<fstream>
#include"recaptcha.cpp"
//#pragma once
using namespace std;
string actnum;
struct ACTSET{
	bool valid;
	int used;
	int cnt;
	int chka,chkb,chkc,chkd;
	int year;
	string str;
	int readactset(string s){
		try{
			valid = 1;
			if(s.size()!=20){
				valid = 0;
				throw "length error!";
			}
			str = s;
			int t1 = (s[0]-'0')*10+(s[1]-'0');
			used = t1%3;
			int t2 = (s[2]-'0')*100+(s[3]-'0')*10+(s[4]-'0');
			if(t2%7!=0){
				valid = 0;
				throw "check error!";
			}
			string t3 = s.substr(5,13-5);
			cnt = atoi(t3.c_str());
			chka = s[14]-'0';
			chkb = s[15]-'0';
			chkc = s[16]-'0';
			year = (s[17]-'0')*10+(s[18]-'0');
			chkd = s[19]-'0';
			//b
			int ckb = 0;
			for(int i = 0;i<=4;i++){
				ckb += s[i]-'0';
			}
			ckb = ckb%10;
			if(ckb!=chkb){
				valid = 0;
				throw "check error B!";
			}
			//c
			int ckc = 0;
			for(int i = 0;i<=4;i++){
				ckc *= s[i]-'0';
				ckc = ckc%10;
			}
			if(ckc!=chkc){
				valid = 0;
				throw "check error C!";
			}
			//a
			int cka = 0;
			for(int i = 5;i<=13;i++){
				cka += s[i]-'0';
			}
			cka = cka%10;
			if(cka!=chka){
				valid = 0;
				throw "check error A!";
			}
			//d
			int ckd = 0;
			for(int i = 14;i<=18;i++){
				ckd += s[i]-'0';
			}
			ckd = ckd%10;
			if(ckd!=chkd){
				valid = 0;
				throw "check error D!";
			}
			//ok
			cout<<"checked\n";
		}
		catch(const char *e){
			if(valid==0) used=3;
			cout<<"read act set error:"<<e<<endl;
		}
	}
};
ACTSET actset;
bool isjihuo(){
	return actset.valid==1;
}
int readact(){
	ifstream ifs("activation\\activation.ini");
	ifs>>actnum;
	actset.readactset(actnum);
	ifs.close();
	cout<<"read activation num:"<<actnum<<endl;
}
int drawbut(){
	settextcolor(WHITE);
	settextstyle(36,18,"");
	string s = "当前激活状况-";
	s+=((actset.valid==1)?"已激活":"未激活");
	outtextxy(0,0,s.c_str());
	outtextxy(0,40,"输入激活码");
	string num[12] = {" 0"," 1"," 2"," 3"," 4"," 5",
	" 6"," 7"," 8"," 9","退出","确认"};
	for(int i = 0;i<12;i++){
		setfillcolor(BLACK);
		setlinecolor(YELLOW);
		fillrectangle(i*50,150,i*50+50,200);
		settextcolor(WHITE);
		settextstyle(24,12,"");
		outtextxy(i*50+1,175-12,num[i].c_str());
	}
	//激活码信息
	string t;
	switch(actset.used){
		case 0:t="批量激活版 ";break;
		case 1:t="单独激活版 ";break;
		case 2:t="admin      ";break;
		case 3:t="未激活     ";break;
	}
	settextstyle(24,12,"");
	outtextxy(0,225,t.c_str());
	string s1 = "年份:"+actset.year;
	outtextxy(0,250,s1.c_str());
	string s2 = "激活码:"+actset.str;
	outtextxy(0,250,s2.c_str());
	outtextxy(0,275,"(c)Hjhm v2.0");
	outtextxy(5,105+15,"--------------------");
}//admin pw like:02002000000000040251
int runact(){
	drawbut();
	string t = "";
	while(1){
		MOUSEMSG msg;
		msg = GetMouseMsg();
		if(msg.uMsg == WM_LBUTTONDOWN){
			if(msg.y>150&&msg.y<200){
				int p = msg.x/50;
				if(p<10){
					if(t.size()<20)t+=(char)('0'+p);
				}
				else if(p==10){
					break;
				}
				else if(p==11){
					if(t.size()==20){
						int r = mainrecaptcha();
						cls();
						drawbut();
						string s = (r==1 ? "验证通过":"验证不通过");
						settextstyle(24,12,"");
						outtextxy(0,300,s.c_str());
						if(r==0)continue;
						ofstream ofs("activation\\activation.ini");
						ofs<<t;
						ofs.close();
						readact();
						t.clear();
						drawbut();
					}
				}
				settextcolor(WHITE);
				settextstyle(24,12,"");
				string ts = t+"                     ";
				outtextxy(5,105,ts.c_str());
			}
		}
	}
}
int activationmain(){
	readact();
	runact();
	return 0;
}

