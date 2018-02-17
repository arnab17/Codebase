// Incomplete

#include<bits/stdc++.h>
using namespace std;

#define MAXN 1000000
#define MAX 1000009

struct node{
	int l;
	int r;
};
struct node a[MAX],qq[MAX];

int arr[MAX],segtree[4*MAX];

map<int,int>mp;
map<int,int>::iterator ii;

void build_segtree(int low,int high,int pos){
	if(low==high){
		segtree[pos]=arr[low];
		return;
	}
	int mid=(low+high)/2;
	build_segtree(low,mid,2*pos+1);
	build_segtree(mid+1,high,2*pos+2);
	segtree[pos]=max(segtree[2*pos+1],segtree[2*pos+2]);
}
int query_segtree(int low,int high,int qlow,int qhigh,int pos){
	if(low>high)
		return INT_MIN;
	if(qlow>high||qhigh<low)
		return INT_MIN;
	if(qlow<=low&&qhigh>=high)
		return segtree[pos];
	int mid=(low+high)/2;
	int ret = max(query_segtree(low,mid,qlow,qhigh,2*pos+1),query_segtree(mid+1,high,qlow,qhigh,2*pos+2));
	return ret;
}

int main(){
	int n,q,i;
	scanf("%d",&n);
	for(i=0;i<n;++i){
		scanf("%d %d",&a[i].l,&a[i].r);
		mp[a[i].l]=1;
		mp[a[i].r]=1;
	}
	scanf("%d",&q);
	for(i=0;i<q;++i){
		scanf("%d %d",&qq[i].l,&qq[i].r);
		mp[qq[i].l]=1;
		mp[qq[i].r]=1;
	}
	int counter=1;
	for(ii=mp.begin();ii!=mp.end();++ii){
		ii->second=counter++;
	}
	for(i=0;i<n;++i){
		arr[mp[a[i].l]-1]+=1;
		arr[mp[a[i].r]]-=1;
	}
	for(i=1;i<MAX;++i){
		arr[i]=arr[i-1]+arr[i];
	}
	build_segtree(0,MAXN,0);
	for(i=0;i<q;++i){
		int l=qq[i].l-1;
		int r=qq[i].r-1;
		int ans=query_segtree(0,MAXN,l,r,0);
		printf("%d\n",ans);
	}
	return 0;
}
