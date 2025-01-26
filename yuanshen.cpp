#include<bits/stdc++.h>
#include<graphics.h>
#include <easyx.h>
using namespace std;
int ysmain(){
	cout<<"请先同意隐私协议\n\n";
	ifstream file("yuanshen\\ysxy.txt", ios::binary | ios::ate); // 以二进制模式打开文件
    if (file) {
        streamsize size = file.tellg();
        file.seekg(0, ios::beg);
        string content(size, ' ');
        file.read(&content[0], size);
        content.resize(size);
        cout << content << endl;
    } else {
        cout << "Unable to open file" << endl;
    }
    cout<<"\n\n是否同意:是\n正在跳转\n";
	system("start https://ys-api.mihoyo.com/event/download_porter/link/ys_cn/official/pc_default");
}
