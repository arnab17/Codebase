// http://codeforces.com/contest/455/problem/B

#include<bits/stdc++.h>
using namespace std;

#define MAX 26

typedef struct trie_node trie_node_t;
struct trie_node{
	int data;
	int win; // indicates the state of game is winning
	int loose; // indicates the state of game is losing
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
	pNode->win=-1;
	pNode->loose=-1;
	for(int i=0;i<MAX;++i){
		pNode->children[i]=NULL;
	}
	return pNode;
}
void init(trie_t *pTrie){
	pTrie->cnt=0;
	pTrie->root=get_node();
}
void insert(trie_t *pTrie,string str){
	int level,index,length=str.length();
	trie_node_t *pCrawl=pTrie->root;
	pTrie->cnt++;
	for(level=0;level<length;++level){
		index=str[level]-'a';
		if(!pCrawl->children[index]){
			pCrawl->children[index]=get_node();
		}
		pCrawl=pCrawl->children[index];
	}
	pCrawl->data=pTrie->cnt;
}
void solve(trie_node_t *pNode){
	if(pNode->win!=-1) return;
	int wins=0,looses=0,count=0;
	for(int i=0;i<MAX;++i){
		if(pNode->children[i]!=NULL){
			count++;
			solve(pNode->children[i]);
			if(pNode->children[i]->win==0) wins=1;
			if(pNode->children[i]->loose==0) looses=1;
		}
	}
	if(count!=0){
		pNode->win=wins;
		pNode->loose=looses;
	}
	else{
		pNode->win=0;
		pNode->loose=1;
	}
}

int main(){
	int n,k,i;
	string str;
	trie_t trie;
	init(&trie);
	scanf("%d %d",&n,&k);
	for(i=0;i<n;++i){
		cin>>str;
		insert(&trie,str);
	}
	solve(trie.root);
	int wins=trie.root->win;
	int looses=trie.root->loose;
	if(wins==0){
		printf("Second");
	}
	else if(wins==1&&looses==1){
		printf("First");
	}
	else if(wins==1&&looses==0){
		if(k%2==0){
			printf("Second");
		}
		else{
			printf("First");
		}
	}
	return 0;
}
