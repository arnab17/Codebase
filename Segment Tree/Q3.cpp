#include<bits/stdc++.h>
using namespace std;

#define MAX 100009

int arr[MAX],segtree[4*MAX];

void build_segtree(int low,int high,int pos){
	if(low==high){
		segtree[pos]=arr[low];
		return;
	}
	int mid=(low+high)/2;
	build_segtree(low,mid,2*pos+1);
	build_segtree(mid+1,high,2*pos+2);
	segtree[pos]=segtree[2*pos+1]+segtree[2*pos+2];
}
void update_segtree(int low,int high,int qlow,int qhigh,int pos,int delta){
	if(low>high)
		return;
	if(qlow>high||qhigh<low)
		return;
	if(qlow<=low&&qhigh>=high){
		if(delta==-1){
			printf("%d\n",segtree[pos]);
			segtree[pos]=0;
		}
		else{
			segtree[pos]+=delta;
		}
		return;
	}
	int mid=(low+high)/2;
	update_segtree(low,mid,qlow,qhigh,2*pos+1,delta);
	update_segtree(mid+1,high,qlow,qhigh,2*pos+2,delta);
	segtree[pos]=segtree[2*pos+1]+segtree[2*pos+2];
}
int query_segtree(int low,int high,int qlow,int qhigh,int pos){
	if(low>high)
		return 0;
	if(qlow>high||qhigh<low)
		return 0;
	if(qlow<=low&&qhigh>=high)
		return segtree[pos];
	int mid=(low+high)/2;
	return query_segtree(low,mid,qlow,qhigh,2*pos+1)+query_segtree(mid+1,high,qlow,qhigh,2*pos+2);
}
int main(){
	int t,n,q,i,l,r,tt,ch,delta;
	scanf("%d",&t);
	for(tt=1;tt<=t;++tt){
		scanf("%d %d",&n,&q);
		for(i=0;i<n;++i)
			scanf("%d",&arr[i]);
		build_segtree(0,n-1,0);
		printf("Case %d:\n",tt);
		while(q--){
			scanf("%d",&ch);
			if(ch==1){
				scanf("%d",&l);
				update_segtree(0,n-1,l,l,0,-1);
			}
			else if(ch==2){
				scanf("%d %d",&l,&delta);
				update_segtree(0,n-1,l,l,0,delta);
			}
			else if(ch==3){
				scanf("%d %d",&l,&r);
				int ans=query_segtree(0,n-1,l,r,0);
				printf("%d\n",ans);
			}
		}
	}
	return 0;
}
