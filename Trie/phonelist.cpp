// http://www.spoj.com/problems/PHONELST/

#include<bits/stdc++.h>
using namespace std;

#define MAX 10
#define MAXC 19
#define MAXN 100009

char str[MAXN][MAXC];

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
void insert(trie_t *pTrie,char key[MAXC]){
	int level,index,length=strlen(key);
	trie_node_t *pCrawl=pTrie->root;
	pTrie->cnt++;
	for(level=0;level<length;++level){
		index=key[level]-'0';
		if(!pCrawl->children[index]){
			pCrawl->children[index]=get_node();
		}
		pCrawl=pCrawl->children[index];
	}
	pCrawl->data=pTrie->cnt;
}
bool search(trie_t *pTrie,char key[MAXC]){
	int level,index,length=strlen(key);
	trie_node_t *pCrawl=pTrie->root;
	int word_cnt=0;
	for(level=0;level<length;++level){
		index=key[level]-'0';
		pCrawl=pCrawl->children[index];
		if(pCrawl->data!=0) ++word_cnt;
	}
	if(word_cnt>1) return false;
	else return true;
}
int main(){
	int t,n,i;
	trie_t trie;
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		init(&trie);
		for(i=0;i<n;++i){
			scanf("%s",str[i]);
			if(str[i][0]=='\n'){
				scanf("%s",str[i]);
			}
			insert(&trie,str[i]);
		}
		bool flag=true;
		for(i=0;i<n;++i){
			bool temp=search(&trie,str[i]);
			if(!temp) flag=false;
		}
		if(flag) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
