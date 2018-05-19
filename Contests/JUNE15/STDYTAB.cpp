#include<bits/stdc++.h>
using namespace std;

#define MAX 2009
#define ll long long
#define MOD 1000000000

ll ways[MAX][MAX],cum[MAX][MAX],nCr[2*MAX][2*MAX];

void pre(){
    for(int i=0;i<=4000;i++)
        nCr[i][0] = 1 ;
    for(int i=1;i<=4000;i++)
        for(int j=1;j<=i;j++)
            nCr[i][j] = ( nCr[i-1][j-1] + nCr[i-1][j] ) % MOD ;
}

int main(){
	int t,n,m,i,j;
	scanf("%d",&t);
	
	pre();
	
	while(t--){
		scanf("%d %d",&n,&m);
		for(i=1;i<=n;++i){
			for(j=0;j<=m;++j){
				if(i==1){
					ways[i][j]=nCr[m+j-1][m-1];
					cum[i][j]=ways[i][j];
					if(j-1>=0) cum[i][j]+=cum[i][j-1];
					if(cum[i][j]>=MOD) cum[i][j]%=MOD;
				}	
				else{
					ways[i][j]=(cum[i-1][j]*nCr[m+j-1][m-1]);
					if(ways[i][j]>=MOD) ways[i][j]%=MOD;
					cum[i][j]=ways[i][j];
					if(j-1>=0) cum[i][j]+=cum[i][j-1];
					if(cum[i][j]>=MOD) cum[i][j]%=MOD;
				}
			}
		}
		ll ans=0;
		for(i=0;i<=m;++i){
			ans=ans+ways[n][i];
			if(ans>=MOD) ans%=MOD;
		}	
		printf("%lld\n",ans);
	}	
	return 0;
}
