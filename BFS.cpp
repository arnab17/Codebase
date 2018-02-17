#include<bits/stdc++.h>
using namespace std;

#define MAX 100009

bool visited[MAX];
vector<int>G[MAX];

void bfs(int start){
	queue<int>Q;
	Q.push(start);
	while(!Q.empty()){
		int vertex=Q.front();
		Q.pop();
		visited[vertex]=true;
		cout<<vertex<<endl;
		for(int i=0;i<G[vertex].size();++i){
			if(!visited[G[vertex][i]]){
				Q.push(G[vertex][i]);
			}
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
	bfs(1);
	return 0;
}
