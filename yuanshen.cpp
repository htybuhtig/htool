#include<bits/stdc++.h>
#include<graphics.h>
#include <easyx.h>
using namespace std;
int ysmain(){
	cout<<"����ͬ����˽Э��\n\n";
	ifstream file("yuanshen\\ysxy.txt", ios::binary | ios::ate); // �Զ�����ģʽ���ļ�
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
    cout<<"\n\n�Ƿ�ͬ��:��\n������ת\n";
	system("start https://ys-api.mihoyo.com/event/download_porter/link/ys_cn/official/pc_default");
}
