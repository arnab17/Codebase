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
