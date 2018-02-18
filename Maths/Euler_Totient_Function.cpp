1. Euler Totient Function counts the number of positive integers less than n that are coprime to n.
   That is, phi(n) is the number of m such that 1 <= m < n and gcd(m,n) = 1.
2. If gcd(a,b) = 1 , then phi(a*b) = phi(a) * phi(b).
3. If p is prime, phi(p) = p-1.
4. If n = p1^k1 p2^k2 p3^k3......pm^km then
   phi(n) = n (1 - 1/p1) (1 - 1/p2) ...... (1 - 1/pm).
   
IMPLEMENTATION :-

for(int i=1;i<=n;++i) phi[i] = (i-1);
for(int i=2;i*i<=n;++i){
    if(phi[i]==(i-1)){
          for(int j=i*i;j<=n;j+=i){
              phi[j]=(phi[j]/i)*(i-1);
          }
    }
}

5. The sum of values of totient functions of all divisors of n is equal to n.
   summation ( phi(d) ) = n ; where d is a divisor of n.
