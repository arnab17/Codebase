#include<bits/stdc++.h>
using namespace std;

#define MAX 2
#define MAXN 100009
#define INT_SIZE 32

int arr[MAXN];

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
		pCrawl->pass++;
	}
	pCrawl->data=num;
}
int search(trie_t *pTrie,int k,int num){
	int level;
	trie_node_t* pCrawl=pTrie->root;
	int ans=0;
	for(level=INT_SIZE-1;level>=0;--level){
		bool val=num&(1<<level);
		bool cbit=k&(1<<level);
		bool flag=false;
		if(val){
			if(pCrawl->children[val]){
				if(cbit){
					trie_node_t *temp=pCrawl->children[val];
					ans=ans+temp->pass;
				}
				else{
					flag=true;
					pCrawl=pCrawl->children[val];
				}
			}
			if(pCrawl->children[1-val]){
				if(cbit){
					flag=true;
					pCrawl=pCrawl->children[1-val];
				}
			}
		}
		else{
			if(pCrawl->children[val]){
				if(cbit){
					trie_node_t *temp=pCrawl->children[val];
					ans=ans+temp->pass;
				}
				else{
					flag=true;
					pCrawl=pCrawl->children[val];
				}
			}
			if(pCrawl->children[1-val]){
				if(cbit){
					flag=true;
					pCrawl=pCrawl->children[1-val];
				}
			}
		}
		if(!flag) break;
	}
	return ans;
}
int main(){
	int t,n,i,k;
	trie_t trie;
	scanf("%d",&t);
	while(t--){
		init(&trie);
		scanf("%d %d",&n,&k);
		for(i=0;i<n;++i) scanf("%d",&arr[i]);
		insert(&trie,0);
		int xor_sum=0;
		long long int ans=0;
		for(i=0;i<n;++i){
			xor_sum=xor_sum^arr[i];
			ans=ans+(long long int)search(&trie,k,xor_sum);
			insert(&trie,xor_sum);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
