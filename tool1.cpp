#include<bits/stdc++.h>
#include<graphics.h>
#include <easyx.h>
#include"cppwchar.cpp"
#include"cppgraphics.cpp"
#include"weather2.cpp"
#include"astar2.cpp"
//#include"poj.cpp"
#include"yuanshen.cpp"
#include"activation.cpp"
#include"recaptcha.cpp"
#include"timer.cpp"
#include<windows.h>
/* graphics.h
https://blog.csdn.net/m0_74835231/article/details/142927676
-leasyx
*/
using namespace std;
void start(){
	cout<<"如遇bug请点击本窗口关闭\n";
	IMAGE background;
    loadimage(&background, "lib\\background.jpg");
    putimage(0,400-337,&background);
	IMAGE img;
    loadimage(&img, "lib\\icon.jpg", 63, 63);
    putimage(600-63,0,&img);
	IMAGE text;
    loadimage(&text, "lib\\text.jpg");
    transparentimage(0,0,text);
    readact();//加载激活码
}
void initbutton(){
	IMAGE img;
    loadimage(&img, "lib\\mihoyo.png", 150, 150);
    putimage(450,250,&img);
	//1-1
	setfillcolor(BLACK);
	setlinecolor(YELLOW);
	fillrectangle(0,0,100,100);
	settextcolor(WHITE);
	settextstyle(24,12,"");
	outtextxy(1,38, "天气");
	//1-2
	setfillcolor(BLACK);
	setlinecolor(YELLOW);
	fillrectangle(100,0,200,100);
	settextcolor(WHITE);
	settextstyle(24,12,"");
	outtextxy(101,38, "算法演示");
	//1-3
	setfillcolor(BLACK);
	setlinecolor(YELLOW);
	fillrectangle(200,0,300,100);
	settextcolor(WHITE);
	settextstyle(24,12,"");
	outtextxy(202,38, "POJ状况");
	//1-4
	setfillcolor(BLACK);
	setlinecolor(YELLOW);
	fillrectangle(300,0,400,100);
	IMAGE img1;
    loadimage(&img1, "lib\\yslogo.png", 98, 98);
    putimage(301,1,&img1);
	//1-5
	setfillcolor(BLACK);
	setlinecolor(YELLOW);
	fillrectangle(400,0,500,100);
	settextcolor(WHITE);
	settextstyle(24,12,"");
	outtextxy(402,38, "激活");
	//1-6
	setfillcolor(BLACK);
	setlinecolor(YELLOW);
	fillrectangle(500,0,600,100);
	settextcolor(WHITE);
	settextstyle(24,12,"");
	outtextxy(502,38, "时钟");
	//2-1
	setfillcolor(BLACK);
	setlinecolor(YELLOW);
	fillrectangle(0,100,100,200);
	settextcolor(WHITE);
	settextstyle(24,12,"");
	outtextxy(1,138, "验证码");
	//2-1
	setfillcolor(BLACK);
	setlinecolor(YELLOW);
	fillrectangle(100,100,200,200);
	settextcolor(WHITE);
	settextstyle(24,12,"");
	outtextxy(101,138, "红绿灯");
	//4-1
	setfillcolor(BLACK);
	setlinecolor(YELLOW);
	fillrectangle(0,300,100,400);
	settextcolor(WHITE);
	settextstyle(24,12,"");
	outtextxy(1,338, "退出");
    if(!isjihuo()){
		IMAGE img1;
	    loadimage(&img1,"lib\\jh.png");
	    transparentimage(101,300,img1);
	}
}
void exittool(){
	setlinecolor(BLACK);
	setfillcolor(BLACK);
	fillrectangle(0,0,600,400);
	settextcolor(WHITE);
	settextstyle(64,32,"");
	outtextxy(0,0, "正在退出");
	outtextxy(0,70, "Auctor:HTY");
	IMAGE img;
    loadimage(&img, "lib\\icon.jpg", 150, 150);
    putimage(450,250,&img);
	settextstyle(48,24,"");
	for(int i = 0;i<=100;i++){
		string s = "已完成"+to_string(i)+"%";
		outtextxy(0,140,s.c_str());
		Sleep(25);
		if(i==20){
			outtextxy(0,192, "清理图形缓存");
		}
		else if(i==40){
			outtextxy(0,192, "释放内存    ");
		}
		else if(i==60){
			outtextxy(0,192, "请稍后      ");
		}
		else if(i==80){
			outtextxy(0,192, "即将完成    ");
		}
		else if(i==100){
			outtextxy(0,192, "正在关闭窗口");
		}
	}
	closegraph();
	cout<<"now exit htool\n";
}
int run(){
	while(1){
		MOUSEMSG msg;
		msg = GetMouseMsg();
		if(msg.uMsg == WM_LBUTTONDOWN){
			if(msg.y>=0 && msg.y<100){
				if(msg.x>=0&&msg.x<100&&isjihuo()){
					cls();
					mainweather();
					return 0;
				}
				if(msg.x>=100&&msg.x<200&&isjihuo()){
					cls();
					mainastar();
					return 0;
				}
				if(msg.x>=200&&msg.x<300&&isjihuo()){
					cls();
					//pojalivetest();
					return 0;
				}
				if(msg.x>=300&&msg.x<400&&isjihuo()){
					cls();
					ysmain();
					return 0;
				}
				if(msg.x>=400&&msg.x<500){
					cls();
					activationmain();
					return 0;
				}
				if(msg.x>=500&&msg.x<600&&isjihuo()){
					cls();
					maintimer();
					return 0;
				}
			}
			if(msg.y>=100 && msg.y<200){
				if(msg.x>=0&&msg.x<100&&isjihuo()){
					cls();
					mainrecaptcha(0,5);
					return 0;
				}
				if(msg.x>=100&&msg.x<200&&isjihuo()){
					cls();
					mainrecaptcha(5,0);
					return 0;
				}
			}
			if(msg.y>=200 && msg.y<300){
			}
			if(msg.y>=300 && msg.y<400){
				if(msg.x>=0&&msg.x<100){
					exittool();
					return 1;
				}
			}
		}
	}
}
int main(){
	initgraph(600,400,SHOWCONSOLE);
	start();
	Sleep(1000);
	while(1){
		cls();
		initbutton();
		int r = run();
		if(r==1) return 0;
	}
	return 0;
}

