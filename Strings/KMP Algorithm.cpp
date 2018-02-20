#include<bits/stdc++.h>
using namespace std;

#define MAX 100009

int lps[MAX];
char txt[MAX],pat[MAX];

void compute_lps_array(int m){
	int len=0;
	int i=1;
	lps[0]=0;
	while(i<m){
		if(pat[i]==pat[len]){
			len++;
			lps[i]=len;
			i++;
		}
		else{
			if(len!=0){
				len=lps[len-1];
			}
			else{
				lps[i]=0;
				i++;
			}
		}
	}
}

void KMPsearch(){
	int m=strlen(pat);
	int n=strlen(txt);
	compute_lps_array(m);
	int i=0,j=0;
	while(i<n){
		if(pat[j]==txt[i]){
			j++;
			i++;
		}
		if(j==m){
			printf("Pattern found at index %d\n",i-j);
			j=lps[j-1];
		}
		else if(i<n&&pat[j]!=txt[i]){
			if(j!=0){
				j=lps[j-1];
			}
			else{
				i=i+1;
			}
		}
	}
}

int main(){
	cin>>txt;
	cin>>pat;
	KMPsearch();
	return 0;
}
