// Minimum Spanning Tree : Kruskal's Algorithm

#include<bits/stdc++.h>
using namespace std;

#define MAX 100009

int size[MAX],parent[MAX];
pair<int,pair<int,int> >p[MAX];

void make_set(int vertices){
	for(int i=1;i<=vertices;++i){
		parent[i]=i;
		size[i]=1;
	}
}

int find_set(int vertex){
	if(vertex==parent[vertex]){
		return vertex;
	}
	int root;
	root=find_set(parent[vertex]);
	parent[vertex]=root;
	return root;
}

void union_set(int a,int b){
	int root_a=find_set(a);
	int root_b=find_set(b);
	if(size[root_a]<size[root_b]){
		parent[root_a]=parent[root_b];
		size[root_b]+=size[root_a];
	}
	else{
		parent[root_b]=parent[root_a];
		size[root_a]+=size[root_b];
	}
}

int kruskals(int vertices,int edges){
	sort(p,p+edges);
	//sort(p,p+edges,greater<pair<int,pii> >());
	make_set(vertices);
	int minimum_cost=0;
	for(int i=0;i<edges;++i){
		int u=p[i].second.first;
		int v=p[i].second.second;
		int cost=p[i].first;
		if(find_set(u)!=find_set(v)){
			minimum_cost+=cost;
			union_set(u,v);
		}
	}
	return minimum_cost;
}

int main(){
	int vertices,edges,vertex1,vertex2,weight;
	cin>>vertices>>edges;
	for(int i=0;i<edges;++i){
		cin>>vertex1>>vertex2>>weight;
		p[i]=make_pair(weight,make_pair(vertex1,vertex2));
	}
	int ans=kruskals(vertices,edges);
	printf("%d\n",ans);
	return 0;
}
