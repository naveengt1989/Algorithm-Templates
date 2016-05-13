///////////////////////////////////// 

// File Name :

// Purpose :

// Creation Date : 18-12-2014

// Last Pified : <Pified_date>

// Created By : Naveen Thomas 

//////////////////////////////////////
#include <bits/stdc++.h>
#define LL long long
#define MOD 1000000007
#define MAX 100003
using namespace std;
LL mpow(LL a, LL n)
{
    LL ret=1;
    LL b=a;
    while(n)
    {
        if(n&1LL)ret=(ret*b)%MOD;
        b=(b*b)%MOD;
        n>>=1LL;
    }
    return (LL)ret;
}
LL fact[MAX],ifact[MAX];
void pre()
{
    LL i;
    fact[0]=1;ifact[0]=1;fact[1]=1;ifact[1]=1;
    for(i=2; i<MAX; i++)
    {
        fact[i]=(i*fact[i-1])%MOD;
        ifact[i]=mpow(fact[i],MOD-2);
    }
}
LL choose(LL n,LL r)
{
    if(n<r)return 0ll;
    LL ret1=(ifact[r]*ifact[n-r])%MOD;
    LL ret=(ret1*fact[n])%MOD;
    return ret;
}

int main()
{
	pre();
	LL N=7; LL r=3; 
	cout<<choose(N,r)<<"\n";
	return 0;
}
