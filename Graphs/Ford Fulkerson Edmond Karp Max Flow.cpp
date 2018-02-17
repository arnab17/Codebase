/*
	Ford Fulkerson Edmond Karp Max Flow Algorithm
*/

#include<bits/stdc++.h>
using namespace std;

#define MAX 1009

int f,s,t;
vector<pair<int,int> >G[MAX];

void augmentPath(int v,int minEdge){
	if(v==s){  // managed to get back to source
		f=minEdge;  // minEdge of the path
		return;
	}
	else if(p.count(v)){  // augment if there is a path
		// we need adjmat for fast lookup here
		augmentPath(p[v],min(minEdge,adjmat[p[v]][v]));
		adjmat[p[v]][v]-=f; // forward edges -> decreases
		adjmat[v][p[v]]+=f; // backward edges -> increases
	}
}

void max_flow(){
	map<int,int>p; // parent map to reconstruct path
	int max_flow=0;
	while(1){ // this will run max O(VE) times
		f=0;
		queue<int>q; map<int,int>dist; // O(E) BFS and record path p
		q.push(s); dist[s]=0; // start from source
		while(!q.empty()){
			int u=q.front(); q.pop();
			if(u==t) break;
			for(ii=G[u].begin();ii!=G[u].end();++ii){
				if(adjmat[u][ii->first]>0&&!dist.count(ii->first)){
					dist[ii->first]=dist[u]+1;
					q.push(ii->first);
					p[ii->first]=u;
				}
			}
		}
		augmentPath(t,INF); // path augmentation in O(V)
		if(f==0) break;
		max_flow+=f;
	}
	printf("%d\n",max_flow);
}

int main(){
	int vertices,edges,vertex1,vertex2;
	cin>>vertices>>edges;
	for(i=0;i<edges;++i){
		cin>>vertex1>>vertex2>>weight;
		adjmat[vertex1][vertex2]=weight;
		adjmat[vertex2][vertex1]=0;
		//G[vertex1].push_back(make_pair(vertex2,weight));
	}
	max_flow(s,t);
}
