#include<bits/stdc++.h>
using namespace std;

#define MAX 131079

struct node{
	int data;
	int action; // 1 - OR  2 - XOR
};
struct node segtree[4*MAX];

int arr[MAX];

void build_segtree(int low,int high,int pos){
	if(low==high){
		segtree[pos].data=arr[low];
		segtree[pos].action=1;
		return;
	}
	int mid=(low+high)/2;
	build_segtree(low,mid,2*pos+1);
	build_segtree(mid+1,high,2*pos+2);
	if(segtree[2*pos+1].action==1){
		segtree[pos].data=(segtree[2*pos+1].data|segtree[2*pos+2].data);
		segtree[pos].action=2;
	}
	else if(segtree[2*pos+1].action==2){
		segtree[pos].data=(segtree[2*pos+1].data^segtree[2*pos+2].data);
		segtree[pos].action=1;
	}
}
void update_segtree(int low,int high,int qlow,int qhigh,int pos,int delta){
	if(low>high)
		return;
	if(qlow>high||qhigh<low)
		return;
	if(qlow<=low&&qhigh>=high){
		segtree[pos].data=delta;
		return;
	}
	int mid=(low+high)/2;
	update_segtree(low,mid,qlow,qhigh,2*pos+1,delta);
	update_segtree(mid+1,high,qlow,qhigh,2*pos+2,delta);
	if(segtree[2*pos+1].action==1){
		segtree[pos].data=(segtree[2*pos+1].data|segtree[2*pos+2].data);
		segtree[pos].action=2;
	}
	else if(segtree[2*pos+1].action==2){
		segtree[pos].data=(segtree[2*pos+1].data^segtree[2*pos+2].data);
		segtree[pos].action=1;
	}
}
int main(){
	int n,m,i,p,b,ns;
	scanf("%d %d",&ns,&m);
	n=1;
	for(i=1;i<=ns;++i) n=n*2;
	for(i=0;i<n;++i)
		scanf("%d",&arr[i]);
	build_segtree(0,n-1,0);
	while(m--){
		scanf("%d %d",&p,&b);
		p=p-1;
		update_segtree(0,n-1,p,p,0,b);
		printf("%d\n",segtree[0]);
	}
	return 0;
}
