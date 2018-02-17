#include<bits/stdc++.h>
using namespace std;

#define MAX 100009
#define DFS_WHITE -1

vector<int>G[MAX];
stack<int>dfs_scc;
int in_stack[MAX];
int dfs_num[MAX],dfs_low[MAX];

int dfsNumberCounter;

void tarjanSCC(int u){
	dfs_num[u]=dfs_low[u]=dfsNumberCounter++;
	dfs_scc.push(u); in_stack[u]=true;
	for(int i=0;i<G[u].size();++i){
		if(dfs_num[G[u][i]]==DFS_WHITE){
			tarjanSCC(G[u][i]);
			dfs_low[u]=min(dfs_low[u],dfs_low[G[u][i]]);
		}
		else if(in_stack[G[u][i]]){
			dfs_low[u]=min(dfs_low[u],dfs_num[G[u][i]]);
		}
	}
	if(dfs_low[u]==dfs_num[u]){
		while(dfs_scc.top()!=u){
			int vertex=dfs_scc.top();
			in_stack[vertex]=false;
			dfs_scc.pop();
			printf("%d ",vertex);
		}
		int vertex=dfs_scc.top();
		dfs_scc.pop();
		in_stack[vertex]=false;
		printf("%d\n",vertex);
	}
}
int main(){
	int vertices,edges,vertex1,vertex2;
	cin>>vertices>>edges;
	for(int i=0;i<edges;++i){
		cin>>vertex1>>vertex2;
		G[vertex1].push_back(vertex2);
	}
	dfsNumberCounter=0;
	memset(dfs_num,DFS_WHITE,sizeof dfs_num);
	for(int i=1;i<=vertices;++i){
		if(dfs_num[i]==DFS_WHITE){
			tarjanSCC(i);
		}
	}
	return 0;
}
