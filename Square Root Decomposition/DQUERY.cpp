http://www.spoj.com/problems/DQUERY/

#include<bits/stdc++.h>
using namespace std;

#define MAXN 30009
#define MAXE 1000009
#define MAXQ 200009

#define BLOCK 174 // ~sqrt(N)

struct node{
	int l;
	int r;
	int ind;
};
struct node q[MAXQ];

int arr[MAXN],fans[MAXQ],mark[MAXE],ans=0;

bool comp(struct node x,struct node y){
	if(x.l/BLOCK!=y.l/BLOCK){
		// different blocks, so sort by block
		return x.l/BLOCK < y.l/BLOCK;
	}
	// same block, so sort by r value
	return x.r < y.r;
}

void add(int pos){
	mark[arr[pos]]++;
	if(mark[arr[pos]]==1){
		ans++;
	}
}

void remove(int pos){
	mark[arr[pos]]--;
	if(mark[arr[pos]]==0){
		ans--;
	}
}

int main(){
	int n,m,i;
	scanf("%d",&n);
	for(i=0;i<n;++i) scanf("%d",&arr[i]);
	
	scanf("%d",&m);
	for(i=0;i<m;++i){
		scanf("%d %d",&q[i].l,&q[i].r);
		q[i].l--; q[i].r--;
		q[i].ind=i;
	}
	
	sort(q,q+m,comp);
	memset(mark,0,sizeof mark);
	
	int currentL=0,currentR=0;
	for(i=0;i<m;++i){
		
		while(currentL<q[i].l){
			remove(currentL);
			currentL++;
		}
		while(currentL>q[i].l){
			add(currentL-1);
			currentL--;
		}
		while(currentR<=q[i].r){
			add(currentR);
			currentR++;
		}
		while(currentR>(q[i].r+1)){
			remove(currentR-1);
			currentR--;
		}
		fans[q[i].ind]=ans;
	}
	
	for(i=0;i<m;++i){
		printf("%d\n",fans[i]);
	}
	
	return 0;
}
