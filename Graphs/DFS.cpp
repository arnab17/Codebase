#include<bits/stdc++.h>
using namespace std;

#define MAX 100009

bool visited[MAX];
vector<int>G[MAX];

void dfs(int start){
	visited[start]=true;
	cout<<start<<endl;
	for(int i=0;i<G[start].size();++i){
		if(!visited[G[start][i]]){
			dfs(G[start][i]);
		}
	}
}

int main(){
	int vertices,edges,vertex1,vertex2;
	cin>>vertices>>edges;
	for(int i=0;i<edges;++i){
		cin>>vertex1>>vertex2;
		G[vertex1].push_back(vertex2);
		G[vertex2].push_back(vertex1);
	}
	memset(visited,false,sizeof visited);
	dfs(1);
	return 0;
}
