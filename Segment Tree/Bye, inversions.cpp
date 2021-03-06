// https://www.codechef.com/problems/ACM14KP2

#include<stdio.h>
int bit_length;
int a[200001],b[200001],bit[200009];
void initialize(int bit[])
{
    int i;
    for(i=0;i<bit_length;++i)
        bit[i]=0;
}
int comp(const void *a,const void *b)
{
    int *x=(int*)a;
    int *y=(int*)b;
    return *x-*y;
}
int get_next(int index)
{
    return index+(index&-index);
}
int get_parent(int index)
{
    return index-(index&-index);
}
void update_bit(int bit[],int value,int index)
{
    while(index<bit_length)
    {
        bit[index]+=value;
        index=get_next(index);
    }
}
long long int sum_bit(int bit[],int index)
{
    long long int sum=0;
    while(index>0)
    {
        sum+=bit[index];
        index=get_parent(index);
    }
    return sum;
}
int b_search(int b[],int value,int n)
{
    int lb=0;
    int ub=n-1;
    while(lb<=ub)
    {
        int mid=lb+((ub-lb)/2);
        if(b[mid]==value)
            return mid;
        if(b[mid]>value)
            ub=mid-1;
        else
            lb=mid+1;
    }
    return -1;
}
int check_array(int a[],int n)
{
    int mark[100001]={0},i;
    for(i=0;i<n;++i)
        mark[a[i]]+=1;
    for(i=0;i<100001;++i)
    {
        if(mark[i]>1)
            return 1;
    }
    return 0;
}
int main()
{
    int t,n,i,j,index,flag;
    long long int inv_count,k;
    scanf("%d",&t);
    for(j=0;j<t;++j)
    {
        scanf("%d %lld",&n,&k);
        bit_length=n+1; flag=0;
        initialize(bit);
        for(i=0;i<n;++i)
        {
            scanf("%d",&a[i]);
            b[i]=a[i];
        }
        flag=check_array(a,n);
        qsort(b,n,sizeof(int),comp);
        for(i=0;i<n;++i)
        {
            index=b_search(b,a[i],n);
            a[i]=index;
        }
        inv_count=0;
        for(i=n-1;i>=0;--i)
        {
            inv_count+=sum_bit(bit,a[i]);
            update_bit(bit,1,a[i]+1);
        }
        if(inv_count>k||inv_count==k)
        {
            k=inv_count-k;
        }
        else
        {
            long long int temp=k-inv_count;
            if(temp%2==0)
                k=0;
            else
            {
                if(flag==1)
                    k=0;
                else
                    k=1;
            }
        }
        printf("Case %d: %lld\n",j+1,k);
    }
    return 0;
}
