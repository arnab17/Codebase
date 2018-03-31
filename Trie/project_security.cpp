#include<bits/stdc++.h>
using namespace std;

#define MAX 2
#define MAXN 300009
#define INT_SIZE 32

int A[MAXN];

typedef struct trie_node trie_node_t;
struct trie_node{
	int data;
	int pass;
	trie_node_t *children[MAX];
};
typedef struct trie trie_t;
struct trie{
	int cnt;
	trie_node_t *root;
};
trie_node_t* get_node(){
	trie_node_t *pNode=(trie_node_t*)malloc(sizeof(trie_node_t));
	pNode->data=0;
	pNode->pass=0;
	for(int i=0;i<MAX;++i)
		pNode->children[i]=NULL;
	return pNode;
}
void init(trie_t *pTrie){
	pTrie->cnt=0;
	pTrie->root=get_node();
}
void insert(trie_t *pTrie,int num){
	int level;
	trie_node_t *pCrawl=pTrie->root;
	pTrie->cnt++;
	for(level=INT_SIZE-1;level>=0;--level){
		bool val=num&(1<<level);
		if(!pCrawl->children[val]){
			pCrawl->children[val]=get_node();
		}
		pCrawl=pCrawl->children[val];
		pCrawl->pass++;
	}
	pCrawl->data=num;
}
int search(trie_t *pTrie,int num){
	int level;
	trie_node_t *pCrawl=pTrie->root;
	for(level=INT_SIZE-1;level>=0;--level){
		bool val=num&(1<<level);
		trie_node_t *n1=NULL;
		if(pCrawl->children[val]) n1=pCrawl->children[val];
		trie_node_t *n2=NULL;
		if(pCrawl->children[1-val]) n2=pCrawl->children[1-val];
		if(pCrawl->children[val]&&n1->pass!=0){
			pCrawl=pCrawl->children[val];
			pCrawl->pass--;
		}
		else if(pCrawl->children[1-val]&&n2->pass!=0){
			pCrawl=pCrawl->children[1-val];
			pCrawl->pass--;
		}
	}
	return (num^pCrawl->data);
}

int main(){
	int n,i,num;
	trie_t trie;
	init(&trie);
	scanf("%d",&n);
	for(i=0;i<n;++i) scanf("%d",&A[i]);
	for(i=0;i<n;++i){
		scanf("%d",&num);
		insert(&trie,num);
	}
	for(i=0;i<n;++i){
		int temp=search(&trie,A[i]);
		printf("%d ",temp);
	}
	return 0;
}
