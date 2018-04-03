// Mahmoud and Ehab and the xor-MST

#include<bits/stdc++.h>
using namespace std;

#define MAX 100009
#define ll long long

ll pow2[MAX];

void pre(){
	pow2[0]=1;
	for(int i=1;i<=60;++i){
		pow2[i]=pow2[i-1]*2ll;
	}
}

ll calc_cost(ll n){
	int cnt=0;
	while(n>1){
		ll temp=n%2;
		if(temp==0){
			++cnt;
		}
		else{
			break;
		}
		n=n/2;
	}
	return pow2[cnt];
}

int main(){
	ll n;
	cin>>n;
	ll ccost=1,ans=0;
	pre();
	ll bs=1,lf=n;
	while(n>1){
		if(n%2==0){
			n=n/2;
			ans=ans+(n*ccost);
			ccost=ccost*2;
			bs=bs*2;
		}
		else{
			ll excess_cost=calc_cost(lf-bs);
			lf=lf-bs;
			n=n/2;
			ans=ans+(n*ccost)+excess_cost;
			ccost=ccost*2;
			bs=bs*2;
		}
	}
	cout<<ans;
	return 0;
}
