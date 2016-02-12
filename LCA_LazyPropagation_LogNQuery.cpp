
///////////////////////////////////// 

// File Name :

// Purpose :

// Creation Date : 01-06-2015

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
#include <climits>
#define CLR(a, x) memset( a, x, sizeof( a ) )
using namespace std;
#define getcx getchar_unlocked
#define ULL unsigned long long
#define UL unsigned long
#define LL long long
#define vi vector<int>
#define vvi vector<vi>
#define ii pair<int, int>
#define vii vector<ii>
#define FOR(i,a,b) for(int i=a; i<b; i++)
#define MAXN 100002
#define MAXLOG 30

int N;	
vi T;
vi P[MAXLOG];
vvi G;
vi L;
vi tin;
vi tout;
int timer;
int lg;
inline void inp( int &n )//fast input function
{
	n=0;
	unsigned int ch=getchar_unlocked();int sign=1; 
	while( ch < '0' || ch > '9' ){if(ch=='-')sign=-1; ch=getchar_unlocked();}

	while( ch >= '0' && ch <= '9' )
		n = (n<<3)+(n<<1) + ch-'0', ch=getchar_unlocked();
	n=n*sign;
}

//O(N)
void construct()
{
	// construct parent tree 
	for(int i=1; (1<<i) < N; i++ )
	{
		for(int j=0; j<N ; j++)
		{
			if(P[j][i-1] != -1)
				P[j][i] = P[P[j][i-1]][i-1]; 
		}
	}
}

void dfs2(long v,long p)
{
	tin[v]=timer;
	++timer;
	P[v][0]=p;
	if(v!= 1)
		L[v] = L[p]+1;
	for (int i=1;i<=lg;i++)
	{
		P[v][i]=P[P[v][i-1]][i-1];
	}
	for (int i=0;i<G[v].size();i++)
	{
		long to=G[v][i];
		if (to!=p)
			dfs2(to,v);
	}
	++timer;
	tout[v]=timer;
}

void dfs1(int node, int p)
{
	if(p!=-1)
		T[node]=p,L[node]=L[p]+1;
	vi::iterator it;
	for(it=G[node].begin(); it!= G[node].end(); it++)
		if((*it)!=p)dfs1(*it,node);
}

//O(log N) --> lazy propagation
void buildParentTree(int x)
{
	//cout<<"Building Tree\n";
	if(T[x]==0 )
		return;
	P[x][0] = T[x];
	if(P[P[x][0]][0] == 0)
		buildParentTree(P[x][0]);
	for(int i=1; (1<<i) < N; i++ )
	{
		if(P[x][i-1]!=0)
			P[x][i] = P[P[x][i-1]][i-1];
	}
}

bool upper(long a,long b)
{
	return tin[a]<=tin[b]&&tout[a]>=tout[b];
}

//O(log N) --> lazy propagation
int query(int x, int k)
{
	if(T[x] == 0 || T[x] == -1)
		return 0;
	if(P[x][0]==0)
	{
		buildParentTree(x);
	}

	int log;
	for(log=1; (1<<log)<= k; log++ )
		;
	log--;

	int node=x;
	for(int i=log; i>=0 && node!=0; i-- )
	{	
		//cout<<pow(2,i)<<" th parent of node: "<<node<<" = "<<P[node][i]<<"\n";
		if(((k>>i)&1) != 0)
		{
			node = P[node][i];
		}	
	}
	return node;
}

int LCA2(int a, int b)
{
	if (upper(a,b))return a;
	if (upper(b,a))return b;
	for (int i=lg;i>=0;--i)
	{
		if (!upper(P[a][i],b))
			a=P[a][i];
	}
	return P[a][0];
}

int LCA1(int p,int q)
{
	if (L[p] < L[q])
		swap(p,q);
	int log;
	for (log = 1; 1 << log <= L[p]; log++);
	log--;
	int i;
	for (i = log; i >= 0; i--)
		if (L[p] - (1 << i) >= L[q])
			p = P[p][i];
	if (p == q)
		return p;
	for (i = log; i >= 0; i--)
		if (P[p][i] != -1 && P[p][i] != P[q][i])
			p = P[p][i], q = P[q][i];
	return T[p];

}

bool findIntersection(int anc1, int anc2, int a, int b, ii& res)
{
	int start=-1; int end=-1; 
	if(upper(anc1, anc2))
		start = anc2;
	else if(upper(anc2,anc1))	
		start = anc1;

	end = LCA2(a, b);

	if(start!=-1 && end!= -1 && upper(start,end))// valid intersection	
	{
		cout<<start<<" "<<end<<"\n";
		res.first = start, res.second = end;
		return true;
	}
	else
	{
		//cout<<"INVALID INTERSECTION\n";
		return false;
	}

}

vii findSegments(ii a, ii b)
{
	int anc1 = LCA2(a.first, a.second);	
	int anc2 = LCA2(b.first, b.second);
	vii res;
	ii temp;
	if(findIntersection(anc1, anc2, a.first, b.first, temp))
		res.push_back(temp);		
	if(findIntersection(anc1, anc2, a.first, b.second, temp))
		res.push_back(temp);		
	if(findIntersection(anc1, anc2, a.second, b.first, temp))
		res.push_back(temp);		
	if(findIntersection(anc1, anc2, a.second, b.second, temp))
		res.push_back(temp);		

	return res;	
}

// Deletion - O(1)
// Creation - O(1) --> lazy propagation --> effectively O(logN)
// Query - O(logN)
int main()
{
	inp(N);
	T.resize(N+1,-1);
	FOR(i,0,MAXLOG)
		P[i].resize(N+1,0);
	G.resize(N+1);
	L.resize(N+1);
	tin.resize(N+1);
	tout.resize(N+1);
	lg = ceil(log(N));
	
	int i=0;		
	while(i<N-1)
	{
		int u,v;
		inp(u); inp(v);
		G[u].push_back(v);	
		G[v].push_back(u);	
		i++;	
	}
	// construct()
	dfs2(1,1);
	//cout<<LCA2(15,16);
	findSegments(ii(10,11), ii(12,13));
	

	return 0;
}


