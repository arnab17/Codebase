#include<bits/stdc++.h>
using namespace std;

#define MAX 100009
#define ll long long

int x[MAX],y[MAX],ans[MAX];
vector<pair<double,int> >T;

int main(){
	//freopen("inp.txt","r",stdin);
	int n,t,i,m,j,k;
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(i=0;i<n;++i){
			scanf("%d",&m);
			for(j=0;j<m;++j){
				scanf("%d %d",&x[j],&y[j]);
			}
			double area=0.0;
			k=m-1;
			for(j=0;j<m;++j){
				area += ((double)x[k]+(double)x[j])*((double)y[k]-(double)y[j]);
				k=j;
			}
			T.push_back(make_pair(abs(area/2.0),i));
		}
		sort(T.begin(),T.end());
		for(i=0;i<n;++i){
			ans[T[i].second]=i;
		}
		for(i=0;i<n;++i) printf("%d ",ans[i]);
		printf("\n");
		T.clear();
	}
	return 0;
}
