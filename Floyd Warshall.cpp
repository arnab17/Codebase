#include<bits/stdc++.h>
using namespace std;

#define MAX 101
#define MAXINT 1000000000

int dist[MAX][MAX];

void floyd_warshall(int vertices){
	int i,j,k;
	for(k=1;k<=vertices;++k){
		for(i=1;i<=vertices;++i){
			for(j=1;j<=vertices;++j){
				if(dist[i][k]+dist[k][j]<dist[i][j]){
					dist[i][j]=dist[i][k]+dist[k][j];
				}
			}
		}
	}
}

int main(){
	int vertices,edges,vertex1,vertex2,weight;
	cin>>vertices>>edges;
	memset(dist,MAXINT,sizeof dist);
	for(int i=0;i<edges;++i){
		cin>>vertex1>>vertex2>>weight;
		dist[vertex1][vertex2]=weight;
	}
	floyd_warshall(vertices);
	return 0;
}
