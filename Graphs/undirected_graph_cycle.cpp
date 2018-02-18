#include<bits/stdc++.h>
using namespace std;

#define MAX 100009

int edges[MAX][2];

// Disjoint Set : union by rank and path compression

int parent[MAX],size[MAX];

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

bool detect_cycle(int n,int m){
	make_set(n);
	for(int i=0;i<m;++i){
		int u=edges[i][0];
		int v=edges[i][1];
		int p1=find_set(u);
		int p2=find_set(v);
		if(p1==p2){
			// cycle detected
			return true;
		}
		else{
			union_set(u,v);
		}
	}
	return false;
}

int main(){
	int n,m,i;
	cin>>n>>m;
	for(i=0;i<m;++i){
		cin>>edges[i][0]>>edges[i][1];
	}
	bool chk=detect_cycle(n,m);
	cout<<chk<<endl;
	return 0;
}
