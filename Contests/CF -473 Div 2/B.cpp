// Mahmoud and Ehab and the message

#include<bits/stdc++.h>
using namespace std;

#define MAX 100009
#define ll long long

int arr[MAX],mincost[MAX];
vector<string>V;
map<string,int>mp;
map<string,int>::iterator ii;

int main(){
	string str;
	int n,k,m,i,iter,num,x;
	scanf("%d %d %d",&n,&k,&m);
	for(i=0;i<n;++i){
		cin>>str;
		V.push_back(str);		
	}
	for(i=0;i<n;++i){
		scanf("%d",&arr[i]);
	}
	for(iter=0;iter<k;++iter) mincost[iter]=INT_MAX;
	for(iter=0;iter<k;++iter){
		scanf("%d",&x);
		for(i=0;i<x;++i){
			scanf("%d",&num);
			num=num-1;
			mincost[iter]=min(mincost[iter],arr[num]);
			mp.insert(make_pair(V[num],iter));
		}
	}
	ll ans=0;
	for(i=0;i<m;++i){
		cin>>str;
		ii=mp.find(str);
		int gpno=ii->second;
		int temp=mincost[gpno];
		ans=ans+(ll)temp;
	}
	cout<<ans<<endl;
}
