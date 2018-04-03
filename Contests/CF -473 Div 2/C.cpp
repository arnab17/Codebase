// Mahmoud and Ehab and the wrong algorithm

#include<bits/stdc++.h>
using namespace std;

int main(){
	int n,j;
	scanf("%d",&n);
  
	// Incorrect Answer
	if(n<6){
		printf("-1\n");
	}
	else{
		printf("1 2\n");
		printf("1 3\n");
		printf("1 4\n");
		for(j=5;j<=n;++j){
			printf("4 %d\n",j);
		}
	}
	
	// Correct Answer
	for(j=2;j<=n;++j){
		printf("1 %d\n",j);
	}
	
	return 0;
}
