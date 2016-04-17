
///////////////////////////////////// 

// File Name :

// Purpose :

// Creation Date : 18-12-2014

// Last Pified : <Pified_date>

// Created By : Naveen Thomas 

//////////////////////////////////////
#include <string>
#include <vector>
#include <map>
#include <list>
#include <iterator>
#include <set>
#include <queue>
#include <iostream>
#include <sstream>
#include <stack>
#include <deque>
#include <cmath>
#include <memory.h>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <utility> 
#define N 7
#define k 3
#define P 1000003

using namespace std;
// https://comeoncodeon.wordpress.com/2011/10/09/modular-multiplicative-inverse/
typedef long long LL;

long long fact[P], ifact[P];

// calculate : (a^k)%p using fast_exponentiation
long long degree(long long a, long long x)
{
	long long res = 1;
	long long cur = a;

	while (x)
	{
		if (x%2)
		{
			res = (res * cur)%P;
		}
		x /= 2;
		cur = (cur * cur) % P;
	}
	return res;
}

long long combinations() 
{
	long long res = 1;

	// computing numerator --> (n-k+1)*(n-k+2)*..........(n)
	for (long long i = N; i > N- k; --i) 
	{
		long long ti = i;
		/*while(ti % p == 0)
		{
			ti /= p;
		}*/// making sure (res*ti) is smalong long enough
		res = (res *ti)%P;
	}

	// computing denominator  --> 1*2*3*4*...k
	long long denom = 1;
	for (long long i = 1; i <= k; ++i)
	{
		long long ti = i;
		/*while(ti % p == 0)
		{
			ti /= p;
		}*/
		denom = (denom * ti)%P;
	}

	// Denom*X % p = 1. Here, X = (1/Denom)%p. So to find (1/Denom)%p, it is sufficient to find X(Fermat's theorem). (X^-1)%P = (X^P-2)%P 
	res = (res * degree(denom, P-2)) % P;

	return res;
}

/*long long mpow(long long a, long long r)
{
	if(r == 0) return 1;
	long long res = mpow(a,r>>1);
	res *= res; res %= P;
	if(r&1ll)
	{ 
		res *= a; res %= P;
	}
	return res;
}*/

long long mpow(long long a, long long r) 
{
	if(r == 0) return 1;
	long long res = mpow(a,r>>1);
	res *= res; res %= P;
	if(r&1ll)
	{ 
		res *= a; res %= P; 
	}
	return res;
}

long long inv(long long a)
{
	return mpow(a,P-2);
}

long long _choose(long long n, long long r) 
{
	if(n < r) return 0;
	if(r < 0) return 0;
	long long res = fact[n];
	res *= ifact[r]; res %= P;// lucas theorem 
	res *= ifact[n-r]; res %= P;
	return res;
}

long long choose1(long long n, long long r)
{
	if(n < P && r < P) return _choose(n,r);
	long long res = choose1(n/P, r/P);
	res *= _choose(n%P, r%P);
	res %= P;
	return res;
}

void preprocessing1() 
{
	fact[0] = fact[1] = ifact[0] = ifact[1] = 1;
	for(long long i=2;i<P;i++) 
	{
		fact[i] = fact[i-1]*i;
		fact[i] %= P;
		ifact[i] = ifact[i-1]*inv(i);
		ifact[i] %= P;
	}
}

long long fct[N];
long long inV[N];
long long invfct[N];
void preprocessing2(int M) 
{
	fct[0]=fct[1]=1;
	inV[1]=1;
	invfct[0]=invfct[1]=1;
	for(int i=2;i<=M;i++)
	{
		fct[i]=LL(i)*fct[i-1]%P;
		inV[i]=LL(P-inV[P%i])*(P/i)%P;
		invfct[i]=LL(inV[i])*invfct[i-1]%P;
	}
}


int main()
{
	// objective = find (N(Ck)%p

	// Method 1	
	cout << combinations()<<"\n";

	// Method 2
	preprocessing1(); // O(P)
	cout<<choose1(N,k)<<"\n"; // O(log P)


	// Method 3 - to find inverse of first n numbers in O(n) 
	preprocessing2(N);
	cout<<(fct[N] * invfct[k] * invfct[N-k])%P<<"\n"; 

	return 0;
}

//Method 2
// Lucas's Theorem reduces nCr % M to
// (n0Cr0 % M) * (n1Cr1 % M) ... (nkCrk % M)
// Where,
// (nknk-1...n0) is the base M representation of n
// (rkrk-1...r0) is the base M representation of r

// If k's are different, return 0;

// niCri % M => can be calculated using above function



// Memoization:
// nCr = n-1Cr + n-1Cr-1
