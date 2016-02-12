
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
using namespace std;
#define CLOCK_START double start_t = clock();
#define CLOCK_STOP cout << "Took: " << ((clock() - start_t) / CLOCKS_PER_SEC);
#define FOR(i,a,b) for(int i=a; i<b; i++)
#define ii pair<int,int>
#define vi vector<int>
#define CLR(a, x) memmultiset( a, x, sizeof( a ) )
#define LL long long
#define ULL unsigned long long
inline void inp( int &n )//fast input function
{
	n=0;
	unsigned int ch=getchar_unlocked();int sign=1; 
	while( ch < '0' || ch > '9' ){if(ch=='-')sign=-1; ch=getchar_unlocked();}

	while( ch >= '0' && ch <= '9' )
		n = (n<<3)+(n<<1) + ch-'0', ch=getchar_unlocked();
	n=n*sign;
}

vector<int> primes;
void sieve1(int CAP)
{
	vector<bool> flag(CAP, 0);
	for(int i = 2; i < CAP; i++)
	{
		if(flag[i]==false)
			primes.push_back(i);
		if(i <= sqrt(CAP) && flag[i] == false)
		{
			for(int j = i*i; j < CAP; j += i)
			{ 
				if(j % i == 0)
					flag[j] = true;
			}
		}
	}
}
vi factors[1000001];
void sieve2(int CAP)
{
	vector<bool> flag(CAP, 0);
	for(int i = 2; i < CAP; i++)
	{
		if(i <= sqrt(CAP) && flag[i] == false)
		{
			for(int j = i; j < CAP; j += i)
			{ 
				if(j % i == 0)
				{
					factors[j].push_back(i);
					flag[j] = true;
				}
			}
		}
		if(!flag[i])
			factors[i].push_back(i);
	}
}

void printFactors()
{
	for(int i=2; i< 23; i++)
	{
		cout<<i<<" - ";
		for(int j=0; j<factors[i].size(); j++)
		{
			cout<<factors[i][j]<<" ";
		}
		cout<<"\n";
	}
}

void printPrimes()
{
	for(int i=0; i< primes.size(); i++)
	{
		cout<<primes[i]<<"\n";
	}
}

int main()
{
	CLOCK_START
	//sieve2(1000002);	
	sieve1(102);	
	printPrimes();
	/*for(int i=2; i< 23; i++)
	{
		cout<<i<<" - ";
		for(int j=0; j<factors[i].size(); j++)
		{
			cout<<factors[i][j]<<" ";
		}
		cout<<"\n";
	}*/
	//pre();
	int T;
	inp(T);
	while(T--)
	{
		int N; inp(N);
		vector<int> lastOccur(1000001,-1);
		int i=0; int res=1; int prev= 0;
		while(i<N)
		{
			int cur; 
			inp(cur); int mx= -1;
			for(int j=0; j<factors[cur].size(); j++)	
			{
				mx = max(mx, lastOccur[factors[cur][j]]);
				lastOccur[factors[cur][j]] = i;	
			}
			mx = min(i-mx, prev+1);
			res = max(res, mx);
			prev = mx; 
			i++;
		}
		if(res>1)
			cout<<res<<"\n";
		else
			cout<<"-1\n";
	}
	CLOCK_STOP
	return 0;
}


