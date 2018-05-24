// https://www.hackerearth.com/practice/algorithms/dynamic-programming/bit-masking/practice-problems/algorithm/the-ghost-type/

#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define MAX 21
#define MMAX 1048576

ll dp[MAX][MMAX];

ll solve(int ind,int mask,int n){
	if(ind==n){
		return 1;
	}
	if(dp[ind][mask]!=-1) return dp[ind][mask];
	dp[ind][mask]=0;
	for(int i=1;i<=n;++i){
		int bit_status=(mask>>(i-1))&1;
		if(bit_status==0){
			bool flag=true;
			for(int j=1;j<i;++j){
				if((i&j)==j){
					int check_bit=(mask>>(j-1))&1;
					if(!check_bit) flag=false;
				}
			}
			if(flag){
				int new_mask=(1<<(i-1))|mask;
				dp[ind][mask]+=solve(ind+1,new_mask,n);
			}
		}
	}
	return dp[ind][mask];
}

int main(){
	int n;
	scanf("%d",&n);
	memset(dp,-1,sizeof dp);
	ll ans=solve(0,0,n);
	printf("%lld",ans);
	return 0;
}
