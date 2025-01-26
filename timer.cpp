#include <graphics.h>
#include <math.h>
#include <time.h>
#include<bits/stdc++.h>
#include<windows.h>

void drawHand(int xc, int yc, double seconds, int length, int width) {
    int x1 = xc + (int)(length * cos(seconds));
    int y1 = yc - (int)(length * sin(seconds));
    line(xc, yc, x1, y1); // 画针
    rectangle(x1 - width / 2, y1 - width / 2, x1 + width / 2, y1 + width / 2); // 画针尖
}

int maintimer() {
	cout<<"bug\n";
    int xc = 300, yc = 200,cnt=0; // 中心点
    int radius = 150; // 时钟半径
    double pi = 3.14159265358979323846;
	setfillcolor(YELLOW);
	setlinecolor(YELLOW);
    while (cnt<10) { // 循环直到按键中断
		cnt++;
        cleardevice(); // 清屏
        circle(xc, yc, radius); // 画圆圈
        // 获取当前时间
        time_t rawtime;
        struct tm *timeinfo;
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        double hourAngle = (timeinfo->tm_hour % 12 + timeinfo->tm_min / 60.0) * 30; // 时针角度
        double minuteAngle = (timeinfo->tm_min + timeinfo->tm_sec / 60.0) * 6; // 分针角度
        double secondAngle = (timeinfo->tm_sec * 6); // 秒针角度
        // 画时针、分针和秒针
        drawHand(xc, yc, hourAngle, radius * 0.5, 10); // 时针
        drawHand(xc, yc, minuteAngle, radius * 0.8, 5); // 分针
        drawHand(xc, yc, secondAngle, radius * 0.95, 2); // 秒针
        Sleep(1000);
    }
    return 0;
}
