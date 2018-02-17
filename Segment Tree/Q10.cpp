#include<bits/stdc++.h>
using namespace std;

#define MAX 100009

struct node{
	int fs;
	int sc;
};
struct node segtree[4*MAX];

int arr[MAX];

struct node merge_segtree(struct node a,struct node b){
	vector<int>T;
	
	T.push_back(a.fs);
	T.push_back(a.sc);
	T.push_back(b.fs);
	T.push_back(b.sc);
	
	sort(T.begin(),T.end());

	struct node c;
	c.fs=T[3]; c.sc=T[2];
	
	return c;	
}

void build_segtree(int low,int high,int pos){
	if(low==high){
		segtree[pos].fs=arr[low];
		segtree[pos].sc=-1;
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
		segtree[pos].fs=delta;
		segtree[pos].sc=-1;
		return;
	}
	int mid=(low+high)/2;
	update_segtree(low,mid,qlow,qhigh,2*pos+1,delta);
	update_segtree(mid+1,high,qlow,qhigh,2*pos+2,delta);
	segtree[pos]=merge_segtree(segtree[2*pos+1],segtree[2*pos+2]);
}
struct node dummy = {-1,-1};
struct node query_segtree(int low,int high,int qlow,int qhigh,int pos){
	if(low>high)
		return dummy;
	if(qlow>high||qhigh<low)
		return dummy;
	if(qlow<=low&&qhigh>=high)
		return segtree[pos];
	int mid=(low+high)/2;
	struct node n1=query_segtree(low,mid,qlow,qhigh,2*pos+1);
	struct node n2=query_segtree(mid+1,high,qlow,qhigh,2*pos+2);
	if(n1.fs==-1) return n2;
	else if(n2.fs==-1) return n1;
	else return merge_segtree(n1,n2);
}

int main(){
	int n,m,i,q,l,r;
	char ch;
	scanf("%d",&n);
	for(i=0;i<n;++i)
		scanf("%d",&arr[i]);
	build_segtree(0,n-1,0);
	scanf("%d",&q);
	while(q--){
		scanf("%c",&ch);
		while(ch=='\n'){
			scanf("%c",&ch);
		}
		if(ch=='U'){
			scanf("%d %d",&l,&r);
			l=l-1;
			update_segtree(0,n-1,l,l,0,r);
		}
		else{
			scanf("%d %d",&l,&r);
			l=l-1;r=r-1;
			struct node ans=query_segtree(0,n-1,l,r,0);
			printf("%d\n",(ans.fs+ans.sc));
		}
	}
	return 0;
}
