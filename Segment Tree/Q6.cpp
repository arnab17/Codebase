#include<bits/stdc++.h>
using namespace std;

#define MAX 100009
#define ll long long

ll segtree[4*MAX],lazy[4*MAX];

void regular_update_check(int low,int high,int pos){
	if(lazy[pos]!=0){
		segtree[pos]+=(((ll)high-(ll)low+1)*lazy[pos]);
		//if(segtree[pos]>=MOD) segtree[pos]%=MOD;
		if(low!=high){
			lazy[2*pos+1]+=lazy[pos];
			//if(lazy[2*pos+1]>=MOD) lazy[2*pos+1]%=MOD;
			lazy[2*pos+2]+=lazy[pos];
			//if(lazy[2*pos+2]>=MOD) lazy[2*pos+2]%=MOD;
		}
		lazy[pos]=0;
	}
}
void update_segtree(int low,int high,int qlow,int qhigh,int pos,ll delta){
	if(low>high)
		return;
	regular_update_check(low,high,pos);
	if(qlow>high||qhigh<low)
		return;
	if(qlow<=low&&qhigh>=high){
		segtree[pos]+=(((ll)high-(ll)low+1)*delta);
		//if(segtree[pos]>=MOD) segtree[pos]%=MOD;
		if(low!=high){
			lazy[2*pos+1]+=delta;
			//if(lazy[2*pos+1]>=MOD) lazy[2*pos+1]%=MOD;
			lazy[2*pos+2]+=delta;
			//if(lazy[2*pos+2]>=MOD) lazy[2*pos+2]%=MOD;
		}
		return;
	}
	int mid=(low+high)/2;
	update_segtree(low,mid,qlow,qhigh,2*pos+1,delta);
	update_segtree(mid+1,high,qlow,qhigh,2*pos+2,delta);
	segtree[pos]=segtree[2*pos+1]+segtree[2*pos+2];
	//if(segtree[pos]>=MOD) segtree[pos]%=MOD;
}
ll query_segtree(int low,int high,int qlow,int qhigh,int pos){
	if(low>high)
		return 0;
	regular_update_check(low,high,pos);
	if(qlow>high||qhigh<low)
		return 0;
	if(qlow<=low&&qhigh>=high)	
		return segtree[pos];
	int mid=(low+high)/2;
	return query_segtree(low,mid,qlow,qhigh,2*pos+1)+query_segtree(mid+1,high,qlow,qhigh,2*pos+2);
}
int main(){
	int t,n,p,q,c,qq,tt;
	ll v;
	scanf("%d",&t);
	for(tt=1;tt<=t;++tt){
		scanf("%d %d",&n,&qq);
		memset(lazy,0,sizeof lazy);
		memset(segtree,0,sizeof segtree);
		while(qq--){
			scanf("%d",&c);
			if(c==0){
				scanf("%d %d %lld",&p,&q,&v);
				p=p-1; q=q-1;
				update_segtree(0,n-1,p,q,0,v);
			}
			else{
				scanf("%d %d",&p,&q);
				p=p-1; q=q-1;
				ll ans=query_segtree(0,n-1,p,q,0);
				printf("%lld\n",ans);
			}
		}
	}
	return 0;
}
