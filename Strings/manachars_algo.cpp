#include<bits/stdc++.h>
using namespace std;

#define MAX 100009

int T[2*MAX];
char str[MAX],nstr[2*MAX];

int manachars_algo(){
	int index=0;
	int len=2*strlen(str)+1;
	for(int i=0;i<len;++i){
		if(i%2!=0){
			nstr[i]=str[index++];
		}
		else{
			nstr[i]='$';
		}
	}
	int start=0,end=0;
	for(int i=0;i<len;){
		while(start>0&&end<len-1&&nstr[start-1]==nstr[end+1]){
			start--;
			end++;
		}
		T[i]=end-start+1;
		if(end==len-1){
			break;
		}
		int newCenter=end+(i%2 ==0 ? 1 : 0);
		for(int j=i+1;j<=end;++j){
			T[j]=min(T[i-(j-i)],2*(end-j)+1);
			if(j+T[i-(j-i)]/2==end){
				newCenter=j;
				break;
			}
		}
		i=newCenter;
		end=i+T[i]/2;
		start=i-T[i]/2;
	}
	int ans=INT_MIN;
	for(int i=0;i<len;++i){
		int val;
		val=T[i]/2;
		if(ans<val){
			ans=val;
		}
	}
	return ans;
}
int main(){
	scanf("%s",str);
	int ans=manachars_algo();
	cout<<ans<<endl;
	return 0;
}
