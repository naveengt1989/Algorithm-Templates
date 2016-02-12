
///////////////////////////////////// 

// File Name :

// Purpose :

// Creation Date : 13-06-2015

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

typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<vi> vvi;
int N,M; 

struct Node
{
	ii vertex;
	int dist;
	Node(ii x, int y)
	{
		vertex = x; dist = y;
	}
	bool operator<(const Node& x) const
	{	
		if(dist < x.dist)
			return true; 
		else if(dist == x.dist && vertex < x.vertex)	
			return true;	
		else
			return false;
	}
};


void Dijkstra(vector<string>& inp, vii& src, vvi& D)
{
	set<Node> Q;
	for(int i=0; i< src.size(); i++)
	{
		Q.insert(Node(src[i],0));
		if(inp[src[i].first][src[i].second]=='#')
			D[src[i].first][src[i].second]= 1;
		else
			D[src[i].first][src[i].second]= 0;

	}
	//print(Q);
	while(!Q.empty())
	{
		Node top = *Q.begin();
		Q.erase(Q.begin());
		ii v = top.vertex;
		int d = top.dist;
		//cout<<"Node: "<<v.first<<" "<<v.second<<" = "<<d<<"\n";
		ii cur(v.first-1, v.second);
		if (cur.first>=0 && D[cur.first][cur.second] > D[v.first][v.second] + ((inp[cur.first][cur.second]=='#')?1:0))
		{
			if (D[cur.first][cur.second] != INT_MAX)
			{
				Q.erase(Q.find(Node(cur, D[cur.first][cur.second])));
			}
			D[cur.first][cur.second] = D[v.first][v.second] + ((inp[cur.first][cur.second]=='#')?1:0);
			Q.insert(Node(cur, D[cur.first][cur.second]));
		}
		cur = ii(v.first, v.second-1);
		if (cur.second>=0 && D[cur.first][cur.second] > D[v.first][v.second] + ((inp[cur.first][cur.second]=='#')?1:0))
		{
			if (D[cur.first][cur.second] != INT_MAX)
			{
				Q.erase(Q.find(Node(cur, D[cur.first][cur.second])));
			}
			D[cur.first][cur.second] = D[v.first][v.second] + ((inp[cur.first][cur.second]=='#')?1:0);
			Q.insert(Node(cur, D[cur.first][cur.second]));
		}
		cur = ii(v.first+1, v.second);
		if (cur.first<N && D[cur.first][cur.second] > D[v.first][v.second] + ((inp[cur.first][cur.second]=='#')?1:0))
		{
			if (D[cur.first][cur.second] != INT_MAX)
			{
				Q.erase(Q.find(Node(cur, D[cur.first][cur.second])));
			}
			D[cur.first][cur.second] = D[v.first][v.second] + ((inp[cur.first][cur.second]=='#')?1:0);
			Q.insert(Node(cur, D[cur.first][cur.second]));
		}
		cur = ii(v.first, v.second+1);
		if (cur.second<M && D[cur.first][cur.second] > D[v.first][v.second] + ((inp[cur.first][cur.second]=='#')?1:0))
		{
			if (D[cur.first][cur.second] != INT_MAX)
			{
				Q.erase(Q.find(Node(cur, D[cur.first][cur.second])));
			}
			D[cur.first][cur.second] = D[v.first][v.second] + ((inp[cur.first][cur.second]=='#')?1:0);
			Q.insert(Node(cur, D[cur.first][cur.second]));
		}
	}
}
int main()
{
	cin>>N>>M;
	vector<string> inp;
	int i=0;
	ii P,S;
	vii B;
	while(i<N)
	{
		string str; cin>>str;
		inp.push_back(str);
		for(int j=0; j< str.length(); j++)
		{
			if(str[j]=='S')
				S = ii(i,j);
			else if(str[j]=='P')
				P = ii(i,j);
			if(i==0 || j==0 || i==N-1 || j==M-1)
				B.push_back(ii(i,j)); 
		}
		i++;
	}
	vvi D1(N, vi(M, INT_MAX));
	vvi D2(N, vi(M, INT_MAX));
	vvi D3(N, vi(M, INT_MAX));

	vii src; ii target;

	src.push_back(S);
	Dijkstra(inp,src, D1);
	src.clear();

	src.push_back(P);
	Dijkstra(inp,src, D2);

	Dijkstra(inp,B, D3);
	int res = INT_MAX;
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<M; j++)
		{
			cout<<i<<" "<<j<<" "<<D1[i][j]<<" "<<D2[i][j]<<" "<<D3[i][j]<<" "<<inp[i][j]<<"\n";
			if(inp[i][j]=='#')
				res = min(res, D1[i][j]+D2[i][j]+ D3[i][j]-2);	
			else	
				res = min(res, D1[i][j]+D2[i][j]+ D3[i][j]);	
		}
	}
	cout<<res<<"\n";
	return 0;
}



