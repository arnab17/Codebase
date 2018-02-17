#include<bits/stdc++.h>
using namespace std;

#define MAX 100009
#define ll long long
#define MOD 1000000007

ll arr[MAX],segtree[4*MAX];

struct node{
	ll A;
	ll M;
	ll F;
	bool flag;
};
struct node lazy[4*MAX];

void init(){
	for(int i=0;i<4*MAX;++i){
		lazy[i].A=0;
		lazy[i].M=1;
		lazy[i].F=0;
		lazy[i].flag=false;
	}
}
void build_segtree(int low,int high,int pos){
	if(low==high){
		segtree[pos]=arr[low];
		return;
	}
	int mid=(low+high)/2;
	build_segtree(low,mid,2*pos+1);
	build_segtree(mid+1,high,2*pos+2);
	segtree[pos]=segtree[2*pos+1]+segtree[2*pos+2];
	if(segtree[pos]>=MOD) segtree[pos]=segtree[pos]%MOD;
}
void regular_update_check(int low,int high,int pos){
	if(lazy[pos].flag){
		segtree[pos]=(high-low+1)*lazy[pos].F;
		if(segtree[pos]>=MOD) segtree[pos]%=MOD;
		segtree[pos]=(segtree[pos]*lazy[pos].M)+((high-low+1)*lazy[pos].A);
		if(segtree[pos]>=MOD) segtree[pos]%=MOD;
		if(low!=high){
			lazy[2*pos+1]=lazy[pos];
			lazy[2*pos+2]=lazy[pos];
		}
		lazy[pos].A=0;
		lazy[pos].M=1;
		lazy[pos].F=0;
		lazy[pos].flag=false;
	}
	else if(lazy[pos].A!=0||lazy[pos].M!=1){
		segtree[pos]=(segtree[pos]*lazy[pos].M)+(high-low+1)*lazy[pos].A;
		if(segtree[pos]>=MOD) segtree[pos]%=MOD;
		if(low!=high){
			lazy[2*pos+1].A=(lazy[2*pos+1].A*lazy[pos].M)+lazy[pos].A;
			if(lazy[2*pos+1].A>=MOD) lazy[2*pos+1].A%=MOD;
			lazy[2*pos+1].M=(lazy[2*pos+1].M*lazy[pos].M);
			if(lazy[2*pos+1].M>=MOD) lazy[2*pos+1].M%=MOD;
			lazy[2*pos+2].A=(lazy[2*pos+2].A*lazy[pos].M)+lazy[pos].A;
			if(lazy[2*pos+2].A>=MOD) lazy[2*pos+2].A%=MOD;
			lazy[2*pos+2].M=(lazy[2*pos+2].M*lazy[pos].M);
			if(lazy[2*pos+2].M>=MOD) lazy[2*pos+2].M%=MOD;
		}
		lazy[pos].A=0;
		lazy[pos].M=1;
		lazy[pos].F=0;
		lazy[pos].flag=false;
	}
}
void add_update(int low,int high,int qlow,int qhigh,int pos,ll delta){
	if(low>high) return;
	regular_update_check(low,high,pos);
	if(qlow>high||qhigh<low)
		return;
	if(qlow<=low&&qhigh>=high){
		segtree[pos]+=(high-low+1)*delta;
		if(segtree[pos]>=MOD) segtree[pos]=segtree[pos]%MOD;
		if(low!=high){
			lazy[2*pos+1].A+=delta;
			if(lazy[2*pos+1].A>=MOD) lazy[2*pos+1].A%=MOD;
			lazy[2*pos+2].A+=delta;
			if(lazy[2*pos+2].A>=MOD) lazy[2*pos+2].A%=MOD;
		}
		return;
	}
	int mid=(low+high)/2;
	add_update(low,mid,qlow,qhigh,2*pos+1,delta);
	add_update(mid+1,high,qlow,qhigh,2*pos+2,delta);
	segtree[pos]=segtree[2*pos+1]+segtree[2*pos+2];
	if(segtree[pos]>=MOD) segtree[pos]=segtree[pos]%MOD;
}
void mul_update(int low,int high,int qlow,int qhigh,int pos,ll delta){
	if(low>high) return;
	regular_update_check(low,high,pos);
	if(qlow>high||qhigh<low)
		return;
	if(qlow<=low&&qhigh>=high){
		segtree[pos]=segtree[pos]*delta;
		if(segtree[pos]>=MOD) segtree[pos]%=MOD;
		if(low!=high){
			lazy[2*pos+1].A*=delta;
			if(lazy[2*pos+1].A>=MOD) lazy[2*pos+1].A%=MOD;
			lazy[2*pos+1].M*=delta;
			if(lazy[2*pos+1].M>=MOD) lazy[2*pos+1].M%=MOD;
			lazy[2*pos+2].A*=delta;
			if(lazy[2*pos+2].A>=MOD) lazy[2*pos+2].A%=MOD;
			lazy[2*pos+2].M*=delta;
			if(lazy[2*pos+2].M>=MOD) lazy[2*pos+2].M%=MOD;
		}
		return;
	}
	int mid=(low+high)/2;
	mul_update(low,mid,qlow,qhigh,2*pos+1,delta);
	mul_update(mid+1,high,qlow,qhigh,2*pos+2,delta);
	segtree[pos]=segtree[2*pos+1]+segtree[2*pos+2];
	if(segtree[pos]>=MOD) segtree[pos]=segtree[pos]%MOD;
}
void fix_update(int low,int high,int qlow,int qhigh,int pos,ll delta){
	if(low>high) return;
	regular_update_check(low,high,pos);
	if(qlow>high||qhigh<low)
		return;
	if(qlow<=low&&qhigh>=high){
		segtree[pos]=(high-low+1)*delta;
		if(segtree[pos]>=MOD) segtree[pos]%=MOD;
		if(low!=high){
			lazy[2*pos+1].A=0;
			lazy[2*pos+1].M=1;
			lazy[2*pos+1].F=delta;
			lazy[2*pos+1].flag=true;
			lazy[2*pos+2].A=0;
			lazy[2*pos+2].M=1;
			lazy[2*pos+2].F=delta;
			lazy[2*pos+2].flag=true;
		}
		return;
	}
	int mid=(low+high)/2;
	fix_update(low,mid,qlow,qhigh,2*pos+1,delta);
    fix_update(mid+1,high,qlow,qhigh,2*pos+2,delta);
	segtree[pos]=segtree[2*pos+1]+segtree[2*pos+2];
	if(segtree[pos]>=MOD) segtree[pos]=segtree[pos]%MOD;
}
ll query_segtree(int low,int high,int qlow,int qhigh,int pos){
	if(low>high) return 0;
	regular_update_check(low,high,pos);
	if(qlow>high||qhigh<low) return 0;
	if(qlow<=low&&qhigh>=high) return segtree[pos];
	int mid=(low+high)/2;
	return (query_segtree(low,mid,qlow,qhigh,2*pos+1)+query_segtree(mid+1,high,qlow,qhigh,2*pos+2))%MOD;
}
int main(){
    int n,q,i,x,y,ch;
    ll v;
    scanf("%d %d",&n,&q);
    for(i=0;i<n;++i) scanf("%lld",&arr[i]);
    init();
    build_segtree(0,n-1,0);
    while(q--){
        scanf("%d %d %d",&ch,&x,&y);
        x--; y--;
        if(ch!=4) scanf("%lld",&v);
        if(ch==1) add_update(0,n-1,x,y,0,v);
        else if(ch==2) mul_update(0,n-1,x,y,0,v);
        else if(ch==3) fix_update(0,n-1,x,y,0,v);
        else{
            ll ans=query_segtree(0,n-1,x,y,0);
            printf("%lld\n",ans);
        }
    }
    return 0;
}
