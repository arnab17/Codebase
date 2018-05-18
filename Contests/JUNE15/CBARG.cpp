// https://www.codechef.com/JUNE15/problems/CBARG

#include<bits/stdc++.h>
using namespace std;

#define MAX 100009
#define ll long long

int arr[MAX];

int main(){
	int n,t,i;
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(i=0;i<n;++i) scanf("%d",&arr[i]);
		ll ans=(ll)arr[0];
		for(i=1;i<n;++i){
			if(arr[i]>arr[i-1]){
				ans=ans+((ll)arr[i]-(ll)arr[i-1]);
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
