#include<bits/stdc++.h>
using namespace std;

#define MAX 1009
#define MAXINT 1000000000

int dist[MAX];
vector<pair<pair<int,int>,int> >edges;

// O(VE)

/*
	Is bellman ford applicable for undirected graphs also
	As a matter of fact any undirected graph is also a directed graph.
	You just have to specify any edges {u, v} twice (u, v) and (v, u).
	But don't forget, that this also means any edge with a negative weight will count as a loop. 
	As the Bellman-Ford algorithm ONLY works on graphs that don't contain any cycles with negative weights this actually means your un-directed graph mustn't contain any edges with negative weight.
	If it doesn't its pretty fine to use Bellmann-Ford.
*/

void bellman_ford(int start,int vertices,int edge){
	dist[start]=0;
	for(int i=1;i<vertices;++i){
		for(int j=0;j<edge;++j){
			int u=edges[j].first.first;
			int v=edges[j].first.second;
			int w=edges[j].second;
			if(dist[u]!=MAXINT&&dist[u]+w<dist[v]){
				dist[v]=dist[u]+w;
			}
		}
	}
}

bool check_negative_weight_cycle(int edge){
	for(int i=0;i<edge;++i){
		int u=edges[i].first.first;
		int v=edges[i].first.second;
		int w=edges[i].second;
		if(dist[u]!=MAXINT&&dist[u]+w<dist[v]){
			return true;
		}
	}
	return false;	
}

int main(){
	freopen("inp.txt","r",stdin);
	int src,vertices,edge,vertex1,vertex2,weight;
	cin>>vertices>>edge;
	for(int i=0;i<edge;++i){
		cin>>vertex1>>vertex2>>weight;
		edges.push_back(make_pair(make_pair(vertex1,vertex2),weight));
	}
	cin>>src;
	fill(dist,dist+vertices+1,MAXINT);
	bellman_ford(src,vertices,edge);
	if(!check_negative_weight_cycle(edge)){
		for(int i=1;i<=vertices;++i) cout<<dist[i]<<" "; cout<<endl;
	}
	return 0;
}
