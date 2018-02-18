#include<bits/stdc++.h>
using namespace std;

#define MAX 1000000000
#define MAXLEN 100000

int sz=0;
bool myprimes[MAXLEN+9],nprimes[MAXLEN+9];
int prime[MAXLEN+9];

// Sieve of Eratosthenes

void sieve(int MAXLIMIT){
	int i,j;
	for(i=0;i<=MAXLIMIT;++i)
		myprimes[i]=true;
	myprimes[0]=false; myprimes[1]=false;
	for(i=2;i*i<=MAXLIMIT;++i){
		if(myprimes[i]){
			for(j=i*i;j<=MAXLIMIT;j+=i){
				myprimes[j]=false;
			}
		}
	}
	for(i=2;i<=MAXLIMIT;++i){
		if(myprimes[i]){
			prime[sz++]=i;
		}
	}
}

// Segmented Sieve

void segmented_sieve(int low,int high){
	int half_limit=(int)floor(sqrt((double)high));
	sz=0;
	sieve(half_limit);
	for(int i=0;i<=(high-low);++i){
		nprimes[i]=true;
	}
	for(int i=0;i<sz;++i){
		int lower_num=low/prime[i];
		lower_num=lower_num*prime[i];
		for(int j=lower_num;j<=high;j+=prime[i]){
			if(j<low) continue;
			nprimes[j-low]=false;
		}
	}
	for(int i=0;i<sz;++i){
		if(prime[i]>=low&&prime[i]<=high){
			nprimes[prime[i]-low]=true;
		}
	}
	for(int i=0;i<=(high-low);++i){
		if(nprimes[i]&&(low+i)!=1) printf("%d\n",low+i);
	}
	printf("\n");
}

int main(){
	int t,n,m,i;
	scanf("%d",&t);
	while(t--){
		scanf("%d %d",&m,&n);
		segmented_sieve(m,n);
	}
	return 0;
}
