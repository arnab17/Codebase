#include<bits/stdc++.h>
using namespace std;

#define MAX 1009

string str;
int dp[MAX][MAX];

int solve(int i,int j,int n){
	if(i>j) return 1;
	if(i==j){
		return 1;
	}
	if(dp[i][j]!=-1) return dp[i][j];
	if(str[i]==str[j]){
		return solve(i+1,j-1,n);
	}
	else{
		return 0;
	}
}

int main(){
	int n,i,j,ref=0,i1,i2;
	cin>>str;
	n=str.length();
	memset(dp,-1,sizeof dp);
	for(i=0;i<n;++i){
		for(j=i;j<n;++j){
			dp[i][j]=solve(i,j,n);
			//cout<<i<<" "<<j<<" "<<dp[i][j]<<endl;
			if(dp[i][j]==1){
				int len=(j-i+1);
				if(len>ref){
					ref=len;
					i1=i;
					i2=j;
				}
			}
		}
	}
	cout<<i1<<" "<<i2<<endl;
	return 0;
}
