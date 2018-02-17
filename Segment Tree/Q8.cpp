#include<bits/stdc++.h>
using namespace std;

#define MAX 50009
#define MAXINT 1000000000

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
void update_segtree(int low,int high,int qlow,int qhigh,int pos,int delta){
	if(low>high)
		return;
	if(qlow>high||qhigh<low)
		return;
	if(qlow<=low&&qhigh>=high){
		segtree[pos].sum=delta;
		segtree[pos].left_sum=delta;
		segtree[pos].right_sum=delta;
		segtree[pos].max_sum=delta;
		return;
	}
	int mid=(low+high)/2;
	update_segtree(low,mid,qlow,qhigh,2*pos+1,delta);
	update_segtree(mid+1,high,qlow,qhigh,2*pos+2,delta);
	segtree[pos]=merge_segtree(segtree[2*pos+1],segtree[2*pos+2]);
}
struct node dummy = {MAXINT,MAXINT,MAXINT,MAXINT};
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
	if(lf.sum==MAXINT) return rt;
	else if(rt.sum==MAXINT) return lf;
	else return merge_segtree(lf,rt); 
}

int main(){
	int n,m,i,l,r,c;
	scanf("%d",&n);
	for(i=0;i<n;++i)
		scanf("%d",&arr[i]);
	build_segtree(0,n-1,0);
	scanf("%d",&m);
	while(m--){
		scanf("%d %d %d",&c,&l,&r);
		if(c==0){
			l=l-1;
			update_segtree(0,n-1,l,l,0,r);
		}
		else{
			l=l-1; r=r-1;
			int ans=query_segtree(0,n-1,l,r,0).max_sum;
			printf("%d\n",ans);
		}
	}
	return 0;
}
