#include<bits/stdc++.h>
using namespace std;

#define MAX 100009
#define DFS_WHITE -1

vector<int>G[MAX];
vector<pair<int,int> >bridges;
int dfs_low[MAX],dfs_num[MAX],dfs_parent[MAX];
bool articulation_point[MAX];
int time_counter,dfs_root,root_children;

void articulation_point_and_bridges(int u){
	dfs_low[u]=dfs_num[u]=time_counter++;
	for(int i=0;i<G[u].size();++i){
		if(dfs_num[G[u][i]]==DFS_WHITE){
			dfs_parent[G[u][i]]=u;
			if(u==dfs_root){
				root_children++;
			}
			articulation_point_and_bridges(G[u][i]);
			dfs_low[u]=min(dfs_low[u],dfs_low[G[u][i]]);
			cout<<dfs_low[G[u][i]]<<" "<<dfs_num[u]<<endl;
			if((u!=dfs_root)&&(dfs_low[G[u][i]]>=dfs_num[u])){
				articulation_point[u]=true;
			}
			if(dfs_low[G[u][i]]>dfs_num[u]){
				bridges.push_back(make_pair(u,G[u][i]));
			}
		}
		else if(G[u][i]!=dfs_parent[u]){
			dfs_low[u]=min(dfs_low[u],dfs_num[G[u][i]]);
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
	time_counter=0;
	memset(dfs_num,DFS_WHITE,sizeof dfs_num);
	memset(articulation_point,false,sizeof articulation_point);
	for(int i=1;i<=vertices;++i){
		if(dfs_num[i]==DFS_WHITE){
			dfs_root=i;
			root_children=0;
			articulation_point_and_bridges(i);
			cout<<root_children<<endl;
			if(root_children>1){
				articulation_point[dfs_root]=true;
			}
		}
	}
	cout<<"Articulation Point"<<endl;
	for(int i=1;i<=vertices;++i){
		if(articulation_point[i]){
			cout<<i<<" ";
		}
	}
	cout<<endl;
	cout<<"Bridges"<<endl;
	for(int i=0;i<bridges.size();++i){
		cout<<bridges[i].first<<" "<<bridges[i].second<<endl;
	}
	bridges.clear();
}
