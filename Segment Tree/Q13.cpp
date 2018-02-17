#include<bits/stdc++.h>
using namespace std;

#define MAX 30009

char str[MAX];

struct node{
	int op;
	int cp;
};
struct node segtree[4*MAX];

struct node merge_segtree(struct node a,struct node b){
	struct node c;
	c.op=a.op+b.op;
	c.cp=a.cp+b.cp;
	if(a.op!=0&&b.cp!=0){
		if(a.op>b.cp){
			c.cp=c.cp-b.cp;
			c.op=c.op-b.cp;
		}
		else if(a.op<b.cp){
			c.op=c.op-a.op;
			c.cp=c.cp-a.op;
		}
		else{
			c.op=c.op-a.op;
			c.cp=c.cp-b.cp;
		}
	}
	return c;
}
void build_segtree(int low,int high,int pos){
	if(low==high){
		if(str[low]=='('){
			segtree[pos].op=1;
			segtree[pos].cp=0;
		}
		else{
			segtree[pos].op=0;
			segtree[pos].cp=1;
		}
		return;
	}
	int mid=(low+high)/2;
	build_segtree(low,mid,2*pos+1);
	build_segtree(mid+1,high,2*pos+2);
	segtree[pos]=merge_segtree(segtree[2*pos+1],segtree[2*pos+2]);
}
void update_segtree(int low,int high,int qlow,int qhigh,int pos){
	if(low>high) return;
	if(qlow>high||qhigh<low) return;
	if(qlow<=low&&qhigh>=high){
		segtree[pos].op=(1-segtree[pos].op);
		segtree[pos].cp=(1-segtree[pos].cp);
		return;
	}
	int mid=(low+high)/2;
	update_segtree(low,mid,qlow,qhigh,2*pos+1);
	update_segtree(mid+1,high,qlow,qhigh,2*pos+2);
	segtree[pos]=merge_segtree(segtree[2*pos+1],segtree[2*pos+2]);
}
struct node dummy = {0,0};
struct node query_segtree(int low,int high,int qlow,int qhigh,int pos){
	if(low>high) return dummy;
	if(qlow>high||qhigh<low) return dummy;
	if(qlow<=low&&qhigh>=high)
		return segtree[pos];
	int mid=(low+high)/2;
	struct node lf_node=query_segtree(low,mid,qlow,qhigh,2*pos+1);
	struct node rt_node=query_segtree(mid+1,high,qlow,qhigh,2*pos+2);
	return merge_segtree(lf_node,rt_node);
}

int main(){
	int t,n,m,k;
	t=10;
	while(t--){
		scanf("%d",&n);
		scanf("%s",str); 
		build_segtree(0,n-1,0);
		scanf("%d",&m);
		while(m--){
			scanf("%d",&k);
			if(k==0){
				if(segtree[0].op==segtree[0].cp){
					printf("YES\n");
				}
				else{
					printf("NO\n");
				}
			}
			else{
				update_segtree(0,n-1,k-1,k-1,0);
			}
		}
	}
	return 0;
}
