#include<bits/stdc++.h>
using namespace std;

#define MAX 26

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
	if(pNode){
		pNode->data=0;
		for(int i=0;i<MAX;++i)
			pNode->children[i]=NULL;
	}
	return pNode;
}
void init(trie_t *pTrie){
	pTrie->cnt=0;
	pTrie->root=get_node();
}
/* Time Complexity for inserting a word : O(length of the word) */
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
/* Time Complexity for searching a word : O(length of the word) */
bool search(trie_t *pTrie,string str){
	int level,index,length=str.length();
	trie_node_t *pCrawl=pTrie->root;
	for(level=0;level<length;++level){
		index=str[level]-'a';
		if(!pCrawl->children[index])
			return false;
		pCrawl=pCrawl->children[index];
	}
	return (pCrawl!=NULL&&pCrawl->data!=0);
}
int main(){
	int n,i;
	string str;
	trie_t trie;
	init(&trie);
	cin>>n;
	for(i=0;i<n;++i){
		cin>>str;
		insert(&trie,str);
	}
	for(i=0;i<2*n;++i){
		cin>>str;
		if(search(&trie,str)){
			cout<<"Yes"<<endl;
		}
		else{
			cout<<"No"<<endl;
		}
	}
	return 0;
}
