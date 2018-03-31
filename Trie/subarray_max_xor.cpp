#include<bits/stdc++.h>
using namespace std;

#define MAX 2
#define MAXN 100009
#define INT_SIZE 32

int arr[MAXN];

typedef struct trie_node trie_node_t;
struct trie_node{
	int data;
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
	for(int i=0;i<MAX;++i){
		pNode->children[i]=NULL;
	}
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
	}
	pCrawl->data=num;
}
int search(trie_t *pTrie,int num){
	int level;
	trie_node_t *pCrawl=pTrie->root;
	for(level=INT_SIZE-1;level>=0;--level){
		bool val=num&(1<<level);
		if(pCrawl->children[1-val]){
			pCrawl=pCrawl->children[1-val];
		}
		else if(pCrawl->children[val]){
			pCrawl=pCrawl->children[val];
		}
	}
	return num^(pCrawl->data);
}
int main(){
	int t,n,i;
	trie_t trie;
	scanf("%d",&t);
	while(t--){
		init(&trie);
		scanf("%d",&n);
		for(i=0;i<n;++i) scanf("%d",&arr[i]);
		insert(&trie,0);
		int xor_sum=0,ans=0;
		for(i=0;i<n;++i){
			xor_sum=xor_sum^arr[i];
			int temp=search(&trie,xor_sum);
			ans=max(ans,temp);
			insert(&trie,xor_sum);
		}
		printf("%d\n",ans);
	}
	return 0;
}
