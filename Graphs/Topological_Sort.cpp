#include<bits/stdc++.h>
using namespace std;

#define MAX 100009

int indeg[MAX];
vector<int>G[MAX];

void topological_sort(int n){
	int i;
	vector<int>T; queue<int>Q;
	for(i=1;i<=n;++i){
		if(indeg[i]==0){
			Q.push(i);
		}
	}
	while(!Q.empty()){
		int u=Q.front();
		Q.pop();
		T.push_back(u);
		for(i=0;i<G[u].size();++i){
			int v=G[u][i];
			indeg[v]=indeg[v]-1;
			if(indeg[v]==0){
				Q.push(v);
			}
		}
	}
	if(T.size()!=n){
		// cycle detected
	}
	else{
		for(i=0;i<T.size();++i)
			printf("%d ",T[i]);
	}
}

int main(){
	int vertices,edges,vertex1,vertex2,i;
	cin>>vertices>>edges;
	memset(indeg,0,sizeof indeg);
	for(i=0;i<edges;++i){
		cin>>vertex1>>vertex2;
		G[vertex1].push_back(vertex2);
		indeg[vertex2]+=1;
	}
	topological_sort(vertices);
	return 0;
}
