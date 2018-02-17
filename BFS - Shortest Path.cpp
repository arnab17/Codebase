// Shortest Path in an unweighted graph

#include<bits/stdc++.h>
using namespace std;

#define MAX 100009

int dist[MAX];
vector<int>G[MAX];

void bfs(int src){
	queue<int>Q;
	Q.push(src);
	dist[src]=0;
	while(!Q.empty()){
		int temp=Q.front();
		Q.pop();
		for(int i=0;i<G[src].size();++i){
			if(dist[G[src][i]]==-1){
				Q.push(G[src][i]);
				dist[G[src][i]]=dist[src]+1;
			}
		}
	}
}

int main(){
	int vertices,edges,vertex1,vertex2,src;
	cin>>vertices>>edges;
	for(int i=0;i<edges;++i){
		cin>>vertex1>>vertex2;
		G[vertex1].push_back(vertex2);
		G[vertex2].push_back(vertex1);
	}
	cin>>src;
	memset(dist,-1,sizeof dist);
	bfs(src);
	return 0;
}
