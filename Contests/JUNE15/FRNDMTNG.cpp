#include<bits/stdc++.h>
using namespace std;

int main(){
	int t,t1,t2,T1,T2;
	scanf("%d",&t);
	while(t--){
		scanf("%d %d %d %d",&T1,&T2,&t1,&t2);
		double A=(double)T1*(double)T2;
		
		if(t1>T2){
			// no intercept left on Y axis
		}
		else{
			int intY=(T2-t1);
			if(intY>T1){
				// out of bounds
				double intA=0.5*(double)intY*(double)intY;
				intA=intA-0.5*(double)(intY-T1)*(double)(intY-T1);
				A=A-intA;
			}
			else{
				double intA=0.5*(double)intY*(double)intY;
				A=A-intA;
			}
		}
		
		if(t2>T1){
			// no intercept left on Y axis
		}
		else{
			int intY=(T1-t2);
			if(intY>T2){
				// out of bounds
				double intA=0.5*(double)intY*(double)intY;
				intA=intA-0.5*(double)(intY-T2)*(double)(intY-T2);
				A=A-intA;
			}
			else{
				double intA=0.5*(double)intY*(double)intY;
				A=A-intA;
			}
		}
		
		double deno=(double)T1*(double)T2;
		double ans=A/deno;
		printf("%lf\n",ans);
	}
	return 0;
}
