#include<bits/stdc++.h>
using namespace std;

#define MAX 10009
#define MAXINT -1000000000

struct node{
	int left_sum;
	int right_sum;
	int max_sum;
	int sum;
};
struct node segtree[4*MAX];

int arr[MAX];

struct node merge_segtree(struct node a,struct node b){
	struct node c;
	c.sum=a.sum+b.sum;
	c.left_sum=max(a.left_sum,a.sum+b.left_sum);
	c.right_sum=max(b.right_sum,b.sum+a.right_sum);
	c.max_sum=max(c.left_sum,c.right_sum);
	c.max_sum=max(c.max_sum,a.max_sum);
	c.max_sum=max(c.max_sum,b.max_sum);
	c.max_sum=max(c.max_sum,(a.right_sum+b.left_sum));
	return c;
}
void build_segtree(int low,int high,int pos){
	if(low==high){
		segtree[pos].sum=arr[low];
		segtree[pos].left_sum=arr[low];
		segtree[pos].right_sum=arr[low];
		segtree[pos].max_sum=arr[low];
		return;
	}
	int mid=(low+high)/2;
	build_segtree(low,mid,2*pos+1);
	build_segtree(mid+1,high,2*pos+2);
	segtree[pos]=merge_segtree(segtree[2*pos+1],segtree[2*pos+2]);
}
struct node dummy = {MAXINT,MAXINT,MAXINT,0};
struct node query_segtree(int low,int high,int qlow,int qhigh,int pos){
	if(low>high)
		return dummy;
	if(qlow>high||qhigh<low)
		return dummy;
	if(qlow<=low&&qhigh>=high)
		return segtree[pos];
	int mid=(low+high)/2;
	struct node lf=query_segtree(low,mid,qlow,qhigh,2*pos+1);
	struct node rt=query_segtree(mid+1,high,qlow,qhigh,2*pos+2);
	if(lf.max_sum==MAXINT) return rt;
	else if(rt.max_sum==MAXINT) return lf;
	else return merge_segtree(lf,rt); 
}

int main(){
	int t,n,m,i,x1,y1,x2,y2;
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(i=0;i<n;++i)
			scanf("%d",&arr[i]);
		build_segtree(0,n-1,0);
		scanf("%d",&m);
		while(m--){
			scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
			x1=x1-1; y1=y1-1; x2=x2-1; y2=y2-1;
			if(y1<x2){
				int c1=query_segtree(0,n-1,x1,y1,0).right_sum;
				int c2=query_segtree(0,n-1,x2,y2,0).left_sum;
				int c3=query_segtree(0,n-1,y1+1,x2-1,0).sum;
				printf("%d\n",(c1+c2+c3));
			}
			else{
				int c1=query_segtree(0,n-1,x1,x2-1,0).right_sum+query_segtree(0,n-1,x2,y2,0).left_sum;
				int c2=query_segtree(0,n-1,x2,y1,0).right_sum+query_segtree(0,n-1,y1+1,y2,0).left_sum;
				int c3=query_segtree(0,n-1,x2,y1,0).max_sum;
				printf("%d\n",max(c1,max(c2,c3)));
			}
		}
	}
	return 0;
}
