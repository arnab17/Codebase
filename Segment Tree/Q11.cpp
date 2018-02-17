#include<bits/stdc++.h>
using namespace std;

#define MAX 100009
#define ll long long

int arr[MAX];
ll lazy[4*MAX],segtree[4*MAX][20];

ll modular_pow(ll base, ll exponent){
    ll result = 1;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
            result = (result * base);
        exponent = exponent >> 1;
        base = (base * base);
    }
    return result;
}

void build_segtree(int low,int high,int pos){
	if(low==high){
		for(int i=0;i<20;++i){
			int temp = (arr[low] >> i) & 1;
			segtree[pos][i]=(ll)temp;
		}
		return;
	}
	int mid=(low+high)/2;
	build_segtree(low,mid,2*pos+1);
	build_segtree(mid+1,high,2*pos+2);
	for(int i=0;i<20;++i){
		segtree[pos][i]=segtree[2*pos+1][i]+segtree[2*pos+2][i];
	}
}
void regular_update_check(int low,int high,int pos){
	if(lazy[pos]!=0){
		for(int i=0;i<20;++i){
			int temp = (lazy[pos] >> i) & 1;
			if(temp==1)
				segtree[pos][i]=((ll)high-(ll)low+1ll)-segtree[pos][i];
		}
		if(low!=high){
			lazy[2*pos+1]=lazy[2*pos+1]^lazy[pos];
			lazy[2*pos+2]=lazy[2*pos+2]^lazy[pos];
		}
		lazy[pos]=0;
	}
}
void update_segtree(int low,int high,int qlow,int qhigh,int pos,int delta){
	if(low>high) return;
	regular_update_check(low,high,pos);
	if(qlow>high||qhigh<low) return;
	if(qlow<=low&&qhigh>=high){
		for(int i=0;i<20;++i){
			int temp = (delta >> i) & 1;
			if(temp==1)
				segtree[pos][i]=((ll)high-(ll)low+1)-segtree[pos][i];
		}
		if(low!=high){
			lazy[2*pos+1]=lazy[2*pos+1]^delta;
			lazy[2*pos+2]=lazy[2*pos+2]^delta;
		}
		return;
	}
	int mid=(low+high)/2;
	update_segtree(low,mid,qlow,qhigh,2*pos+1,delta);
	update_segtree(mid+1,high,qlow,qhigh,2*pos+2,delta);
	for(int i=0;i<20;++i){
		segtree[pos][i]=segtree[2*pos+1][i]+segtree[2*pos+2][i];
	}
}
ll query_segtree(int low,int high,int qlow,int qhigh,int pos){
	if(low>high) return 0;
	regular_update_check(low,high,pos);
	if(qlow>high||qhigh<low) return 0;
	if(qlow<=low&&qhigh>=high){
		ll ans=0;
		for(int i=0;i<20;++i){
			ans=ans+(modular_pow(2,i)*segtree[pos][i]);
		}
		return ans;
	}
	int mid=(low+high)/2;
	return query_segtree(low,mid,qlow,qhigh,2*pos+1)+query_segtree(mid+1,high,qlow,qhigh,2*pos+2);
}
int main(){
	int n,m,i,l,r,x,ch;
	scanf("%d",&n);
	for(i=0;i<n;++i)
		scanf("%d",&arr[i]);
	build_segtree(0,n-1,0);
	scanf("%d",&m);
	memset(lazy,0,sizeof lazy);
	while(m--){
		scanf("%d",&ch);
		if(ch==1){
			scanf("%d %d",&l,&r);
			l=l-1; r=r-1;
			ll ans=query_segtree(0,n-1,l,r,0);
			cout<<ans<<endl;
		}
		else{
			scanf("%d %d %d",&l,&r,&x);
			l=l-1; r=r-1;
			update_segtree(0,n-1,l,r,0,x);
		}
	}	
	return 0;
}
