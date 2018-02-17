#include<bits/stdc++.h>
using namespace std;

#define MAX 100009
#define MAXINT 1000000000
#define pii pair<int,int>

int dist[MAX];
vector<pair<int,int> >G[MAX];

// O(E+VlogV)

void dijkstra(int start){
	int u,v,i,c,w;
	priority_queue<pii,vector<pii >,greater<pii > >Q;
	Q.push(pii(0,start));
	dist[start]=0;
	int cnt=0;
	while(!Q.empty()){
		u=Q.top().second;
		c=Q.top().first;
		Q.pop();
		if(c==dist[u]){
			for(i=0;i<G[u].size();++i){
				v=G[u][i].first;
				w=G[u][i].second;
				if(dist[u]+w<dist[v]){
					dist[v]=dist[u]+w;
					Q.push(pii(dist[v],v));
				} 
			}
		}
	}
}

int main(){
	freopen("inp.txt","r",stdin);
	int src,vertices,edges,vertex1,vertex2,weight;
	cin>>vertices>>edges;
	for(int i=0;i<edges;++i){
		cin>>vertex1>>vertex2>>weight;
		G[vertex1].push_back(make_pair(vertex2,weight));
		G[vertex2].push_back(make_pair(vertex1,weight));
	}
	cin>>src;
	fill(dist,dist+vertices+1,MAXINT);
	dijkstra(src);
	for(int i=1;i<=vertices;++i) cout<<dist[i]<<" "; cout<<endl;
	return 0;
}
