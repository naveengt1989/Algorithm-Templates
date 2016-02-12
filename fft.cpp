
///////////////////////////////////// 

// File Name :

// Purpose :

// Creation Date : 14-07-2015

// Last Modified : <modified_date>

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
#include <complex>
using namespace std;
#define CLOCK_START double start_t = clock();
#define CLOCK_STOP cout << "Took: " << ((clock() - start_t) / CLOCKS_PER_SEC);
#define FOR(i,a,b) for(int i=a; i<b; i++)
#define ii pair<int,int>
#define vi vector<int>
#define CLR(a, x) memset( a, x, sizeof( a ) )
#define LL long long
#define ULL unsigned long long
typedef complex<double> base;
#define PI 22/7

const int N = 1 << 13;
inline void inp( int &n )//fast input function
{
	n=0;
	unsigned int ch=getchar_unlocked();int sign=1; 
	while( ch < '0' || ch > '9' ){if(ch=='-')sign=-1; ch=getchar_unlocked();}

	while( ch >= '0' && ch <= '9' )
		n = (n<<3)+(n<<1) + ch-'0', ch=getchar_unlocked();
	n=n*sign;
}

base fa[N], fb[N];
base wlen_pw[N];
inline void fft(base *a, int n, bool invert)
{
	for (int i=1, j=0; i<n; ++i) 
	{
		int bit = n >> 1;
		for (; j>=bit; bit>>=1)
			j -= bit;
		j += bit;
		if (i < j)
			swap (a[i], a[j]);
	}
	for (int len=2; len<=n; len<<=1)
	{
		double ang = 2*M_PI/len * (invert?-1:+1);
		int len2 = len>>1;

		base wlen (cos(ang), sin(ang));
		wlen_pw[0] = base (1, 0);
		for (int i=1; i<len2; ++i)
			wlen_pw[i] = wlen_pw[i-1] * wlen;

		for (int i=0; i<n; i+=len) 
		{
			base t,
			     *pu = a+i,
			     *pv = a+i+len2,
			     *pu_end = a+i+len2,
			     *pw = wlen_pw;
			for (; pu!=pu_end; ++pu, ++pv, ++pw)
			{
				t = *pv * *pw;
				*pv = *pu - t;
				*pu += t;
			}
		}
	}
	if (invert)
		for (int i=0; i<n; ++i)
			a[i] /= n;
}

void multiply (const vector<int> & a, const vector<int> & b, vector<int> & res) 
{
	for(int i=0; i< a.size(); i++)
		fa[i] = a[i];
	for(int i=0; i< b.size(); i++)
		fb[i] = b[i];
	size_t n = 1;
	while (n < max (a.size(), b.size()))  n <<= 1;
	n <<= 1;
	for(int i = a.size(); i < n; i++) fa[i] = 0;
  	for(int i = b.size(); i < n; i++) fb[i] = 0;

	// evaluation of polynomial coefficients O(NlogN)
	fft (fa, n, false),  fft (fb, n, false);
	// multiplication O(N)
	for (size_t i=0; i<n; ++i)
		fa[i] *= fb[i];
	// interpolation O(NlogN)
	fft (fa, n, true);

	res.resize (n);
	for (size_t i=0; i<n; ++i)
	{
		if(fa[i].real() >= 0)
			res[i] = int (fa[i].real() + 0.5);
		else
			res[i] = int (fa[i].real() - 0.5);
	}
}
// http://web.cecs.pdx.edu/~maier/cs584/Lectures/lect07b-11-MG.pdf
// http://e-maxx.ru/algo/fft_multiply
// http://habrahabr.ru/post/113642/
// https://www.hackerrank.com/contests/w16/challenges/white-falcon-and-xor/editorial

int main()
{
	// coefficients of polynomial 1(lowest power first)	
	vector<int> a{1,-1};
	// coefficients of polynomial 2(lowest power first)	
	vector<int> b{1,1};
	// coefficients of resultant polynomial(lowest power first)	
	vector<int> res;
	multiply(a,b,res);
	for(int  i=0; i<res.size(); i++)
	{
		cout<<res[i]<<".x"<<i<<" ";
	}
	cout<<"\n";
	return 0;
}


