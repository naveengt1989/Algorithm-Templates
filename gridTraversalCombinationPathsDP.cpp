
///////////////////////////////////// 

// File Name :

// Purpose :

// Creation Date : 26-05-2015

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
#define CLR(a, x) memset( a, x, sizeof( a ) )
using namespace std;
#define getcx getchar_unlocked
#define LL unsigned long long
//#define LL long long
//#define P 1000000007
#define P 1000000007


LL* fact;
LL* ifact;

LL degree(LL a, LL x)
{
	LL res = 1;
	LL cur = a;

	while (x)
	{
		if (x%2)
		{
			res = (res * cur)%P;
		}
		x /= 2;
		cur = (cur * cur) % P;
	}
	return res%P;
}


LL inv(LL a)
{
	return degree(a,P-2);
}


void preprocessing(int N) 
{
	fact = new LL[N+1];
	ifact = new LL[N+1];
	fact[0] = fact[1] = ifact[0] = ifact[1] = 1;
	for(int i=2;i<=N;i++) 
	{
		fact[i] = fact[i-1]*i;
		fact[i] %= P;
	}
	ifact[N] = inv(fact[N]); 
	for(int i=N;i>0;i--) 
	{
		ifact[i-1] = (ifact[i]*i)%P;
	}
}

LL combination(int N, int k) 
{
	//cout<<fact[N]<<" "<<ifact[k]<<" "<<ifact[N-k]<<"\n";
	return (((fact[N] * ifact[k])%P) * ifact[N-k])%P;
}


LL M,N;
void findWaysInOneD( vector<LL>& X, vector<LL>& D, vector<vector<LL> >& ways)
{
	for(int i=1; i<=N;i++)
	{
		vector<vector<LL> > m(M+1, vector<LL>(D[i]+1, 0));
		for(int j=1; j<= D[i]; j++)
		{
			m[0][j]=1;	
		}	
		for(int j=1; j<= M; j++)
		{
			for(int k=1; k<=D[i]; k++)
			{
				if((k-1) >=1)
					m[j][k] = (m[j][k] +  m[j-1][k-1])%P; 	
				if((k+1) <=D[i])
					m[j][k] = (m[j][k] + m[j-1][k+1])%P; 	
			}
		}
		for(int j=0; j<=M; j++)
		{
			ways[i][j] = m[j][X[i]];
		} 
	}
}

LL findWaysInND(vector<vector<LL> >& ways)
{
	vector<vector<LL> > paths(N+1, vector<LL>(M+1,0));
	for(int i=0; i<=M; i++)
	{
		paths[1][i] = ways[1][i]%P;	
	}
	for(int i=2; i<=N; i++)
	{
		for(int j=0; j<=M; j++)
		{
			for(int k=0; k<=j; k++)
			{
				paths[i][j] += (((paths[i-1][j-k]*ways[i][k])%P)*combination(j,k))%P; 	
				//cout<<k<<" ==>  "<<j-k<<" = "<<(((paths[i-1][j-k]*ways[i][k])%P)*combination(j,k))%P<<" ## "<<paths[i-1][j-k]<<" "<<ways[i][k]<<" "<<combination(j,k)<<" "<<j<<"-C-"<<k<<"\n";
				paths[i][j] = paths[i][j]%P;
			}
			//cout<<" Dimensions: "<<i<<" Moves "<<j<<" = "<<paths[i][j]<<"\n";
		}
	}
	return paths[N][M]%P;
}

int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		cin>>N>>M;
		vector<LL> X(N+1, -1);
		vector<LL> D(N+1, -1);
		for(int i=1; i<=N; i++)
		{
			cin>>X[i];
		}
		for(int i=1; i<=N; i++)
		{
			cin>>D[i];
		}
		preprocessing(M);
		vector<vector<LL> > ways(N+1, vector<LL>(M+1,-1));
		findWaysInOneD(X,D, ways);
		cout<<findWaysInND(ways)<<"\n";	
	}
	return 0;
}


