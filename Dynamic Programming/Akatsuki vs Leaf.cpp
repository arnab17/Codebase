// https://www.hackerearth.com/practice/algorithms/dynamic-programming/bit-masking/practice-problems/algorithm/akatsuki-vs-leaf-circuit/

#include<bits/stdc++.h>
using namespace std;

#define MAX 21
#define MMAX 1048576

int dp[MAX][MMAX];
int x1[MAX][2],x2[MAX][2];

int solve(int i,int mask,int n){
	if(i==n) return 0;
	
	if(dp[i][mask]!=-1) return dp[i][mask];
	
	dp[i][mask]=INT_MAX;
	for(int ii=1;ii<=n;++ii){
		int bit_status=(mask>>(ii-1))&1;
		if(bit_status==0){
			int temp=abs(x1[ii-1][0]-x2[i][0])+abs(x1[ii-1][1]-x2[i][1]);
			int new_mask=(1<<(ii-1))|mask;
			int nexts=solve(i+1,new_mask,n);
			dp[i][mask]=min(dp[i][mask],temp+nexts);
		}
	}
	return dp[i][mask];
}

int main(){
	int n,i;
	scanf("%d",&n);
	for(i=0;i<n;++i){
		scanf("%d %d",&x1[i][0],&x1[i][1]);
	}
	for(i=0;i<n;++i){
		scanf("%d %d",&x2[i][0],&x2[i][1]);
	}
	memset(dp,-1,sizeof dp);
	int ans=solve(0,0,n);
	printf("%d",ans);
	return 0;
}
