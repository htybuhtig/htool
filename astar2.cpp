#include<bits/stdc++.h>
#include<graphics.h>
#include <easyx.h>
#include<windows.h>
#include<queue>
using namespace std;
//600x400 -> 12*8
int g[35][23];
int nl[35][23];//结点的路程
int yl[35][23];//结点到终点预计路程
int vis[35][23];
int drawall(){
	setlinecolor(YELLOW);
	for(int i = 0;i<24;i++){
		for(int j = 0;j<16;j++){
			setfillcolor((g[i][j]==1 ? BLUE : BLACK));
			fillrectangle(i*25,j*25,25+i*25,25+j*25);
		}
	}
}
int redraw(int x,int y){
	setlinecolor(YELLOW);
	setfillcolor((g[x][y]==1 ? BLUE : BLACK));
	fillrectangle(x*25,y*25,25+x*25,25+y*25);
	settextstyle(12,6,"");
	settextcolor(RED);
	string s1 = to_string(nl[x][y]);
	outtextxy(x*25+2,y*25+1,s1.c_str());
	if(x==23&&y==15) settextcolor(GREEN);
	else settextcolor(WHITE);
	string s2 = to_string(yl[x][y]);
	outtextxy(x*25+2,y*25+12,s2.c_str());
}
int setg(){
	for(int i = 0;i<25;i++){
		for(int j = 0;j<16;j++){
			//g[i][j] = ((rand()%5==1) ? 1:0);
			nl[i][j]=999;
		}
	}
	g[0][0]=0;
	g[23][15]=0;
	nl[0][0] = 0;
}
struct QK{
	int x,y;
	int yj,sj;
	QK(int a,int b,int yuji,int shiji){
		x=a;y=b;yj=yuji;sj=shiji;
	}
};
bool cmpqk(const QK& a, const QK& b) {
    return a.yj > b.yj;  // 这里是逆序，优先队列会优先取出yj较小的元素
}
int runastar(){
	priority_queue<QK, vector<QK>, decltype(&cmpqk)> q(cmpqk);
	q.push(QK(0,0,40,0));
	int lx[] = {0,1,0,-1};
	int ly[] = {1,0,-1,0};
	int ans = 9999999;
	while(!q.empty()){
		QK t = q.top();
		q.pop();
		if(t.x==23&&t.y==15){
			ans = t.sj;
			cout<<"ans is:"<<ans<<endl;
			return 0;
		}
		if((t.x>=0&&t.y>=0&&t.x<24&&t.y<16)==0){
			continue;
		}
		redraw(t.x,t.y);
		if(vis[t.x][t.y]==0)Sleep(100);
		vis[t.x][t.y]=1;
		for(int i = 0;i<4;i++){
			int dx = t.x+lx[i];
			int dy = t.y+ly[i];
			int jl = abs(23-dx)+abs(15-dy);
			if(dx>=0&&dy>=0&&dx<24&&dy<16&&g[dx][dy]==0&&(t.sj+1)<=nl[dx][dy]){
				q.push(QK(dx,dy,jl,t.sj+1));
				nl[dx][dy] = t.sj+1;
				yl[dx][dy] = jl;
				redraw(dx,dy);
				//cout<<"now dx:"<<dx<<" dy:"<<dy<<" jl:"<<jl<<endl;
			}
		}
	}
}
int setmap(){
	while(1){
		MOUSEMSG msg;
		msg = GetMouseMsg();
		if(msg.uMsg == WM_LBUTTONDOWN){
			int dx = msg.x/25;
			int dy = msg.y/25;
			if(dx==0&&dy==0) break;
			if(g[dx][dy]==0) g[dx][dy]=1;
			else g[dx][dy]=0;
			cout<<"dx:"<<dx<<" dy:"<<dy<<endl;
			drawall();
		}
	}
}
int mainastar(){
	//srand(time(0)+114);
	drawall();
	cout<<"click 0,0 to exit\n";
	setmap();
	cout<<"setg\n";
	setg();
	cout<<"runastar\n";
	runastar();
	cout<<"wait\n";
	cout<<"click to exit\n";
	while(1){
		MOUSEMSG msg;
		msg = GetMouseMsg();
		if(msg.uMsg == WM_LBUTTONDOWN){
			return 0;
		}
	}
	return 0;
}

