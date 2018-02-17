#include<bits/stdc++.h>
using namespace std;

#define MAX 100009
#define ll long long
#define MOD 1000000007

int q[MAX][3]; ll query_freq[MAX];
ll segtree1[4*MAX],lazy1[4*MAX];
ll segtree[4*MAX],lazy[4*MAX];

void regular_update_check_query(int low,int high,int pos){
	if(lazy1[pos]!=0){
		segtree1[pos]+=(high-low+1)*lazy1[pos];
		if(segtree1[pos]>=MOD) segtree1[pos]%=MOD;
		if(low!=high){
			lazy1[2*pos+1]+=lazy1[pos];
			if(lazy1[2*pos+1]>=MOD) lazy1[2*pos+1]%=MOD;
			lazy1[2*pos+2]+=lazy1[pos];
			if(lazy1[2*pos+2]>=MOD) lazy1[2*pos+2]%=MOD;
		}
		lazy1[pos]=0;
	}
}
void regular_update_check(int low,int high,int pos){
	if(lazy[pos]!=0){
		segtree[pos]+=(high-low+1)*lazy[pos];
		if(segtree[pos]>=MOD) segtree[pos]%=MOD;
		if(low!=high){
			lazy[2*pos+1]+=lazy[pos];
			if(lazy[2*pos+1]>=MOD) lazy[2*pos+1]%=MOD;
			lazy[2*pos+2]+=lazy[pos];
			if(lazy[2*pos+2]>=MOD) lazy[2*pos+2]%=MOD;
		}
		lazy[pos]=0;
	}
}

void update_segtree_query(int low,int high,int qlow,int qhigh,int pos,int delta){
	if(low>high) return;
	regular_update_check_query(low,high,pos);
	if(qlow>high||qhigh<low) return;
	if(qlow<=low&&qhigh>=high){
		segtree1[pos]+=(high-low+1)*delta;
		if(segtree1[pos]>=MOD) segtree1[pos]%=MOD;
		if(low!=high){
			lazy1[2*pos+1]+=delta;
			if(lazy[2*pos+1]>=MOD) lazy[2*pos+1]%=MOD;
			lazy1[2*pos+2]+=delta;
			if(lazy[2*pos+2]>=MOD) lazy[2*pos+2]%=MOD;
		}
		return;
	}
	int mid=(low+high)/2;
	update_segtree_query(low,mid,qlow,qhigh,2*pos+1,delta);
	update_segtree_query(mid+1,high,qlow,qhigh,2*pos+2,delta);
	segtree1[pos]=segtree1[2*pos+1]+segtree1[2*pos+2];
	if(segtree1[pos]>=MOD) segtree1[pos]%=MOD;
}
void update_segtree(int low,int high,int qlow,int qhigh,int pos,ll delta){
	if(low>high) return;
	regular_update_check(low,high,pos);
	if(qlow>high||qhigh<low) return;
	if(qlow<=low&&qhigh>=high){
		segtree[pos]+=(high-low+1)*delta;
		if(segtree[pos]>=MOD) segtree[pos]%=MOD;
		if(low!=high){
			lazy[2*pos+1]+=delta;
			if(lazy[2*pos+1]>=MOD) lazy[2*pos+1]%=MOD;
			lazy[2*pos+2]+=delta;
			if(lazy[2*pos+2]>=MOD) lazy[2*pos+2]%=MOD;
		}
		return;
	}
	int mid=(low+high)/2;
	update_segtree(low,mid,qlow,qhigh,2*pos+1,delta);
	update_segtree(mid+1,high,qlow,qhigh,2*pos+2,delta);
	segtree[pos]=segtree[2*pos+1]+segtree[2*pos+2];
	if(segtree[pos]>=MOD) segtree[pos]%=MOD;
}
ll query_segtree_Q(int low,int high,int qlow,int qhigh,int pos){
	if(low>high) return 0;
	regular_update_check_query(low,high,pos);
	if(qlow>high||qhigh<low) return 0;
	if(qlow<=low&&qhigh>=high) return segtree1[pos];
	int mid=(low+high)/2;
	ll val1 = query_segtree_Q(low,mid,qlow,qhigh,2*pos+1);
	ll val2 = query_segtree_Q(mid+1,high,qlow,qhigh,2*pos+2);
	return (val1+val2)%MOD;
}
ll query_segtree(int low,int high,int qlow,int qhigh,int pos){
	if(low>high) return 0;
	regular_update_check(low,high,pos);
	if(qlow>high||qhigh<low) return 0;
	if(qlow<=low&&qhigh>=high) return segtree[pos];
	int mid=(low+high)/2;
	ll val1 = query_segtree(low,mid,qlow,qhigh,2*pos+1);
	ll val2 = query_segtree(mid+1,high,qlow,qhigh,2*pos+2);
	return (val1+val2)%MOD;
}

int main(){
	int t,n,m,i;
	scanf("%d",&t);
	while(t--){
		scanf("%d %d",&n,&m);
		
		memset(lazy1,0,sizeof lazy1);
		memset(segtree1,0,sizeof segtree1);
		
		for(i=1;i<=m;++i){
			scanf("%d",&q[i][0]);
			scanf("%d %d",&q[i][1],&q[i][2]);
			if(q[i][0]==1){
				update_segtree_query(0,m-1,i-1,i-1,0,1);
			}
			else{
				update_segtree_query(0,m-1,q[i][1]-1,q[i][2]-1,0,1);
			}
		}
		for(i=m-1;i>=0;--i){
			if(q[i+1][0]==2){
				ll freq=query_segtree_Q(0,m-1,i,i,0);
				update_segtree_query(0,m-1,q[i+1][1]-1,q[i+1][2]-1,0,freq);
			}
		}
		
		for(i=0;i<m;++i){
			query_freq[i]=0;
			if(q[i+1][0]==1){
				ll freq = query_segtree_Q(0,m-1,i,i,0);
				query_freq[i]=freq;
			}
		}
		
		memset(lazy,0,sizeof lazy);
		memset(segtree,0,sizeof segtree);
		
		for(i=0;i<m;++i){
			if(q[i+1][0]==1){
				update_segtree(0,n-1,q[i+1][1]-1,q[i+1][2]-1,0,query_freq[i]);
			}
		}
		for(i=0;i<n;++i){
			ll ans=query_segtree(0,n-1,i,i,0);
			printf("%lld ",ans);
		}
		printf("\n");
	}
	return 0;
}
