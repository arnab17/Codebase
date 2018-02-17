#include<bits/stdc++.h>
using namespace std;

#define MAX 100009

char str[MAX];
int segtree[4*MAX],lazy[4*MAX];

void build_segtree(int low,int high,int pos){
	if(low==high){
		segtree[pos]=str[low]-'0';
		return;
	}
	int mid=(low+high)/2;
	build_segtree(low,mid,2*pos+1);
	build_segtree(mid+1,high,2*pos+2);
	segtree[pos]=segtree[2*pos+1]+segtree[2*pos+2];
}
void regular_update_check(int low,int high,int pos){
	if(lazy[pos]!=0){
		segtree[pos]=(high-low+1)-segtree[pos];
		if(low!=high){
			lazy[2*pos+1]=1-lazy[2*pos+1];
			lazy[2*pos+2]=1-lazy[2*pos+2];
		}
		lazy[pos]=0;
	}
}
void update_segtree(int low,int high,int qlow,int qhigh,int pos){
	if(low>high)
		return;
	regular_update_check(low,high,pos);
	if(qlow>high||qhigh<low)
		return;
	if(qlow<=low&&qhigh>=high){
		segtree[pos]=(high-low+1)-segtree[pos];
		if(low!=high){
			lazy[2*pos+1]=1-lazy[2*pos+1];
			lazy[2*pos+2]=1-lazy[2*pos+2];
		}
		return;
	}
	int mid=(low+high)/2;
	update_segtree(low,mid,qlow,qhigh,2*pos+1);
	update_segtree(mid+1,high,qlow,qhigh,2*pos+2);
	segtree[pos]=segtree[2*pos+1]+segtree[2*pos+2];
}
int query_segtree(int low,int high,int qlow,int qhigh,int pos){
	if(low>high)
		return 0;
	regular_update_check(low,high,pos);
	if(qlow>high||qhigh<low)
		return 0;
	if(qlow<=low&&qhigh>=high)
		return segtree[pos];
	int mid=(low+high)/2;
	int c1=query_segtree(low,mid,qlow,qhigh,2*pos+1);
	int c2=query_segtree(mid+1,high,qlow,qhigh,2*pos+2);
	if(c1==1||c2==1){
		return 1;
	}
	else{
		return 0;
	}
}
int main(){
	int t,tt,n,i,q,l,r;
	char ch;
	scanf("%d",&t);
	for(tt=1;tt<=t;++tt){
		scanf("%s",str);
		n=strlen(str);
		build_segtree(0,n-1,0);
		scanf("%d",&q);
		printf("Case %d:\n",tt);
		memset(lazy,0,sizeof lazy);
		while(q--){
			scanf("%c",&ch);
			while(ch=='\n'){
				scanf("%c",&ch);
			}
			if(ch=='I'){
				scanf("%d %d",&l,&r);
				l=l-1; r=r-1;
				update_segtree(0,n-1,l,r,0);
			}
			else if(ch=='Q'){
				scanf("%d",&l); 
				l=l-1;
				int ans=query_segtree(0,n-1,l,l,0);
				printf("%d\n",ans);
			}
		}
	}
	return 0;
}
