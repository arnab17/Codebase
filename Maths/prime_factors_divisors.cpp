// Prime Factorization of a number
// Couting the divisors of a number  using   sieve

void sieve(int MAXLIMIT){
	int i,j;
	for(i=0;i<=MAXLIMIT;++i)
		myprimes[i]=i;
	//myprimes[0]=false; myprimes[1]=false;
	for(i=2;i*i<=MAXLIMIT;++i){
		if(myprimes[i]==i){
			for(j=i*i;j<=MAXLIMIT;j+=i){
				myprimes[j]=i;
			}
		}
	}
	divs[1]=1;
	for(i=2;i<=MAXLIMIT;++i){
		int temp=i; divs[i]=1;
		while(temp>1){
			int p=myprimes[temp];
			int cnt=0;
			while(temp%p==0){
				temp=temp/p;
				cnt+=1;
			}
			divs[i]=divs[i]*(cnt+1);
		}
	}
}
