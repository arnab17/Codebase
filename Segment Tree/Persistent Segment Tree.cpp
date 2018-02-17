#include<bits/stdc++.h>
using namespace std;

#define MAX 200009
#define ll long long
#define MAXINT 1000000

ll segtree[4*MAX],ans[MAX];
int L[20*MAX],R[20*MAX],root[MAX];
int arr[MAX],l[MAX],r[MAX];

int NEXT_FREE_INDEX=1;

void build_segtree(int low,int high,int pos){
	if(low==high){
		segtree[pos]=0;
		return;
	}
	int mid=(low+high)/2;
	L[pos]=NEXT_FREE_INDEX++;
	R[pos]=NEXT_FREE_INDEX++;
	build_segtree(low,mid,L[pos]);
	build_segtree(mid+1,high,R[pos]);
	segtree[pos]=max(segtree[L[pos]],segtree[R[pos]]);
}
int update_segtree(int low,int high,int qpos,int pos,ll delta){
	int ID=NEXT_FREE_INDEX++;
	if(low==high){
		segtree[ID]=delta;
		return ID;
	}
	int mid=(low+high)/2;
	L[ID]=L[pos]; R[ID]=R[pos];
	if(qpos<=mid)
		L[ID]=update_segtree(low,mid,qpos,L[ID],delta);
	else
		R[ID]=update_segtree(mid+1,high,qpos,R[ID],delta);
	segtree[ID]=max(segtree[L[ID]],segtree[R[ID]]);
	return ID;
}
ll query_segtree(int low,int high,int qlow,int qhigh,int pos){
	if(low>high) return 0;
	if(qlow>high||qhigh<low) return 0;
	if(qlow<=low&&qhigh>=high) return segtree[pos];
	int mid=(low+high)/2;
	return max(query_segtree(low,mid,qlow,qhigh,L[pos]),query_segtree(mid+1,high,qlow,qhigh,R[pos]));
}
int main(){
	int n,i;
	
	scanf("%d",&n);
	for(i=1;i<=n;++i) scanf("%d",&arr[i]);
	for(i=1;i<=n;++i) scanf("%d",&l[i]);
	for(i=1;i<=n;++i) scanf("%d",&r[i]);
	
	build_segtree(0,n-1,0); root[0]=0;
	
	for(i=1;i<=n;++i){
		int j=i-l[i]-1;
		ll temp=query_segtree(0,n-1,0,i-2,root[j]);
		ans[i]=(ll)arr[i]+temp;
		ll x=query_segtree(0,n-1,i+r[i]-1,i+r[i]-1,root[i-1]);
		if(ans[i]>x)
			root[i]=update_segtree(0,n-1,i+r[i]-1,root[i-1],ans[i]);
		else
			root[i]=root[i-1];
	}
	
	ll nans=ans[1];
	for(i=2;i<=n;++i){
		nans=max(nans,ans[i]);
	}
	printf("%lld\n",nans);
	return 0;
}
