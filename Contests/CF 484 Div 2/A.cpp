#include<bits/stdc++.h>
using namespace std;

int main(){
	int n,i;
	string str;
	cin>>n;
	cin>>str;
	
	bool sol_flag=true;
	for(i=0;i<str.length();++i){
		if(str[i]=='1'){
			if((i-1)>=0&&str[i-1]=='1'){
				sol_flag=false;
			}
			if((i-1)>=0&&str[i-1]=='0'){
				str[i-1]='2';
			}
			if((i+1)<str.length()&&str[i+1]=='1'){
				sol_flag=false;
			}
			if((i+1)<str.length()&&str[i+1]=='0'){
				str[i+1]='2';
			}
		}
	}
	if(!sol_flag) cout<<"No";
	else{
		for(i=0;i<str.length();++i){
			if(str[i]=='0'){
				sol_flag=false;
			}
		}
		if(!sol_flag) cout<<"No";
		else cout<<"Yes";
	}
	return 0;
}
