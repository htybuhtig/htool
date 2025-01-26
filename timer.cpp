#include <graphics.h>
#include <math.h>
#include <time.h>
#include<bits/stdc++.h>
#include<windows.h>

void drawHand(int xc, int yc, double seconds, int length, int width) {
    int x1 = xc + (int)(length * cos(seconds));
    int y1 = yc - (int)(length * sin(seconds));
    line(xc, yc, x1, y1); // ����
    rectangle(x1 - width / 2, y1 - width / 2, x1 + width / 2, y1 + width / 2); // �����
}

int maintimer() {
	cout<<"bug\n";
    int xc = 300, yc = 200,cnt=0; // ���ĵ�
    int radius = 150; // ʱ�Ӱ뾶
    double pi = 3.14159265358979323846;
	setfillcolor(YELLOW);
	setlinecolor(YELLOW);
    while (cnt<10) { // ѭ��ֱ�������ж�
		cnt++;
        cleardevice(); // ����
        circle(xc, yc, radius); // ��ԲȦ
        // ��ȡ��ǰʱ��
        time_t rawtime;
        struct tm *timeinfo;
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        double hourAngle = (timeinfo->tm_hour % 12 + timeinfo->tm_min / 60.0) * 30; // ʱ��Ƕ�
        double minuteAngle = (timeinfo->tm_min + timeinfo->tm_sec / 60.0) * 6; // ����Ƕ�
        double secondAngle = (timeinfo->tm_sec * 6); // ����Ƕ�
        // ��ʱ�롢���������
        drawHand(xc, yc, hourAngle, radius * 0.5, 10); // ʱ��
        drawHand(xc, yc, minuteAngle, radius * 0.8, 5); // ����
        drawHand(xc, yc, secondAngle, radius * 0.95, 2); // ����
        Sleep(1000);
    }
    return 0;
}
