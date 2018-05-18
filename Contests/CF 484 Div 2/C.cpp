#include<bits/stdc++.h>
using namespace std;

#define MAX 100009

bool visited[MAX];
vector<int>G[MAX];

int ans=0;

int dfs(int u){
	visited[u]=true;
	int val=0;
	for(int i=0;i<G[u].size();++i){
		int v=G[u][i];
		if(!visited[v]){
			int sbn=dfs(v);
			if(sbn%2==0)
				ans++;
			else
				val+=sbn;
		}
	}
	return (val+1);
}

int main(){
	int n,i,u,v;
	scanf("%d",&n);
	for(i=0;i<n-1;++i){
		scanf("%d %d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	if(n%2!=0){
		printf("-1");
	}
	else{
		memset(visited,false,sizeof visited);
		dfs(1);
		printf("%d",ans);
	}
	return 0;
}
