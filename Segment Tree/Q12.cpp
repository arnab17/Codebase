#include<bits/stdc++.h>
using namespace std;

#define MAX 40009
#define MAXN 10000009

int q[MAX][2];
bool lazy[4*MAXN];
bool segtree[4*MAXN];

void regular_update_check(int low,int high,int pos){
	if(lazy[pos]){
		segtree[pos]=true;
		if(low!=high){
			lazy[2*pos+1]=true;
			lazy[2*pos+2]=true;
		}
		lazy[pos]=false;
	}
}

void update_segtree(int low,int high,int qlow,int qhigh,int pos){
	if(low>high) return;
	regular_update_check(low,high,pos);
	if(qlow>high||qhigh<low) return;
	if(qlow<=low&&qhigh>=high){
		segtree[pos]=true;
		if(low!=high){
			lazy[2*pos+1]=true;
			lazy[2*pos+2]=true;
		}
		return;
	}
	int mid=(low+high)/2;
	update_segtree(low,mid,qlow,qhigh,2*pos+1);
	update_segtree(mid+1,high,qlow,qhigh,2*pos+2);
	segtree[pos]=segtree[2*pos+1]&&segtree[2*pos+2];
}

bool query_segtree(int low,int high,int qlow,int qhigh,int pos){
	if(low>high) return true;
	regular_update_check(low,high,pos);
	if(qlow>high||qhigh<low) return true;
	if(qlow<=low&&qhigh>=high) return segtree[pos];
	int mid=(low+high)/2;
	return query_segtree(low,mid,qlow,qhigh,2*pos+1)&&query_segtree(mid+1,high,qlow,qhigh,2*pos+2);
}

int main(){
	int t,n,i,lb,rb;
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		lb=-1; rb=-1;
		memset(lazy,false,sizeof lazy);
		memset(segtree,false,sizeof segtree);
		for(i=0;i<n;++i){
			scanf("%d %d",&q[i][0],&q[i][1]);
			if(lb==-1) lb=q[i][0];
			if(rb==-1) rb=q[i][1];
			lb=min(lb,q[i][0]);
			rb=max(rb,q[i][1]);
		}
		int ans=0;
		for(i=n-1;i>=0;--i){
			if(!query_segtree(lb-1,rb-1,q[i][0]-1,q[i][1]-1,0)){
				update_segtree(lb-1,rb-1,q[i][0]-1,q[i][1]-1,0);
				++ans;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
