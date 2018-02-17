#include<bits/stdc++.h>
using namespace std;

#define MAX 100009

int arr[MAX],segtree[4*MAX],lazy[4*MAX];

void build_segtree(int low,int high,int pos){
	if(low==high){
		segtree[pos]=arr[low];
		return;
	}
	int mid=(low+high)/2;
	build_segtree(low,mid,2*pos+1);
	build_segtree(mid+1,high,2*pos+2);
	segtree[pos]=min(segtree[2*pos+1],segtree[2*pos+2]);
}
void regular_update_check(int low,int high,int pos){
	if(lazy[pos]!=0){
		segtree[pos]+=lazy[pos];
		if(low!=high){
			lazy[2*pos+1]+=lazy[pos];
			lazy[2*pos+2]+=lazy[pos];
		}
		lazy[pos]=0;
	}
}
void update_segtree(int low,int high,int qlow,int qhigh,int pos,int delta){
	if(low>high)
		return;
	regular_update_check(low,high,pos);
	if(qlow>high||qhigh<low)
		return;
	if(qlow<=low&&qhigh>=high){
		segtree[pos]+=delta;
		if(low!=high){
			lazy[2*pos+1]+=delta;
			lazy[2*pos+2]+=delta;
		}
		return;
	}
	int mid=(low+high)/2;
	update_segtree(low,mid,qlow,qhigh,2*pos+1,delta);
	update_segtree(mid+1,high,qlow,qhigh,2*pos+2,delta);
	segtree[pos]=min(segtree[2*pos+1],segtree[2*pos+2]);
}
int query_segtree(int low,int high,int qlow,int qhigh,int pos){
	if(low>high)
		return INT_MAX;
	regular_update_check(low,high,pos);
	if(qlow>high||qhigh<low)
		return INT_MAX;
	if(qlow<=low&&qhigh>=high)
		return segtree[pos];
	int mid=(low+high)/2;
	return min(query_segtree(low,mid,qlow,qhigh,2*pos+1),query_segtree(mid+1,high,qlow,qhigh,2*pos+2));
}
