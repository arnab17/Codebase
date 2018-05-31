// https://www.hackerearth.com/practice/algorithms/dynamic-programming/state-space-reduction/practice-problems/algorithm/bytelandian-gold-coins/

#include<bits/stdc++.h>
using namespace std;

#define MAX1 31
#define MAX2 21
#define ll long long

ll dp[MAX1][MAX2];

ll solve(ll n,int i,int j){
	if(n<12) return n;
	if(dp[i][j]!=-1) return dp[i][j];
	
	ll c1 = n;
	ll c2 = solve(n/2,i+1,j) + solve(n/3,i,j+1) + solve(n/4,i+2,j);
	
	return dp[i][j]=max(c1,c2);
}

int main(){
	ll n;
	while(scanf("%lld",&n)!=EOF){
		memset(dp,-1,sizeof dp);
		ll ans=solve(n,0,0);
	
		printf("%lld\n",ans);
	}
	return 0;
}
