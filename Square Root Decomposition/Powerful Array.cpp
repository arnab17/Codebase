// http://codeforces.com/contest/86/problem/D

#include<bits/stdc++.h>
using namespace std;

#define MAX 200009
#define MAXE 1000009
#define BLOCK 448

#define ll long long

int arr[MAX],mark[MAXE]={0};
ll fans[MAX],ans=0;

struct node{
	int l;
	int r;
	int ind;
};
struct node q[MAX];

bool comp(struct node x,struct node y){
	if(x.l/BLOCK!=y.l/BLOCK){
		return x.l/BLOCK<y.l/BLOCK;
	}
	else{
		return x.r<y.r;
	}
}

void add(int pos){
	ans=ans+((2ll*(ll)mark[arr[pos]]+1ll)*(ll)arr[pos]);
	mark[arr[pos]]++;
}

void remove(int pos){
	ans=ans+((-2ll*(ll)mark[arr[pos]]+1ll)*(ll)arr[pos]);
	mark[arr[pos]]--;
}

int main(){
	int n,m,i;
	scanf("%d %d",&n,&m);
	for(i=0;i<n;++i) scanf("%d",&arr[i]);
	for(i=0;i<m;++i){
		scanf("%d %d",&q[i].l,&q[i].r);
		q[i].l--; q[i].r--;
		q[i].ind=i;
	}
	sort(q,q+m,comp);
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
		cout<<fans[i]<<endl;
	}
	return 0;
}
