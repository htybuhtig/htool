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
	
	setlinecolor(YELLOW);
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
	Sleep(1000);
	while(1){
		MOUSEMSG msg;
		msg = GetMouseMsg();
		if(msg.uMsg == WM_LBUTTONDOWN){
			break;
		}
	}
	return res;
}
int mainrecaptcha(){
	srand(time(0));
	photorecaptcha(4);
}
