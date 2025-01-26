#include<bits/stdc++.h>
#include<algorithm>
using namespace std;
int main(){
	ifstream ifs("ifs.txt");
	ofstream ofs("ofs.txt",ios::app);
	int cnt = 0;
	while(1){
		string a,b,c,d,e,f;
		ifs>>a;
		if(a=="STOP") break;
		ifs>>b>>c>>d>>e>>f;
		string s;
		for(char c : b){
			char ad;
			if(c>='A'&&c<='Z'){
				ad = 'a'+(c-'A');
			}
			else{
				ad = c;
			}
			s+=ad;
		}
		ofs<<s<<" "<<a<<"\n";
		cnt++;
		cout<<"cnt:"<<cnt<<" s:"<<s<<" a:"<<a<<" b:"<<b<<endl;
	}
	ifs.close();ofs.close();
	return 0;
}

