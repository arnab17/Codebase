#include<bits/stdc++.h>
using namespace std;

map<int,int>m1;
map<int,int>m2;
map<int,int>::iterator ii;

char str[400009];

int main(){
	int n,wid,i;
	scanf("%d",&n);
	for(i=0;i<n;++i){
		scanf("%d",&wid);
		m1.insert(make_pair(wid,i));
	}
	scanf("%s",str);
	for(i=0;i<(2*n);++i){
		if(str[i]=='0'){
			ii=m1.begin();
			printf("%d ",ii->second+1);
			m2.insert(make_pair(-ii->first,ii->second));
			m1.erase(ii);
		}
		else{
			ii=m2.begin();
			printf("%d ",ii->second+1);
			m2.erase(ii);
		}
	}
	return 0;
}
