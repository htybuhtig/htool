#include<bits/stdc++.h>
using namespace std;
int main(){
	int used;
	cout<<"输入用途 0批量 1单独 2admin\n";cin>>used;
	string year;
	cout<<"输入年份(like 25)\n";cin>>year;
	int n;
	cout<<"数量\n";cin>>n;
	string fn;
	cout<<"保存文件名\n";cin>>fn;
	ofstream ofs(fn.c_str());
	srand(time(0));
	for(int i = 0;i<n;i++){
		int t1 = (3*rand()+used)%60+12;
		int t2 = (rand()*7)%896+7*15;
		long long t3 = ((rand()<<16) | rand())%899999999+100000000;
		string s1 = to_string(t1)+to_string(t2);
		string s3 = to_string(t3);
		int chka = 0;
		for(char c : s3){
			chka += (c-'0');
		}
		chka%=10;
		int chkb = 0;
		for(char c : s1){
			chkb += (c-'0');
		}
		chkb%=10;
		int chkc = 0;
		for(char c : s1){
			chkc *= (c-'0');
			chkc = chkc%10;
		}
		string s4 = to_string(chka)+to_string(chkb)+
		to_string(chkc)+year;
		int chkd = 0;
		for(char c : s4){
			chkd += (c-'0');
		}
		chkd%=10;
		cout<<s1<<" "<<s3<<" "<<s4<<" "<<chkd<<endl;
		string s = s1+s3+s4+to_string(chkd);
		ofs<<s.substr(0,5)<<" "<<s.substr(5,5)<<" "
		<<s.substr(10,5)<<" "<<s.substr(15,5)<<endl;
	}
	return 0;
}
