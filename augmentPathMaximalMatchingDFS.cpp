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
#include <bitset>
#include <ctime>        
#include <sys/time.h>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <iterator>
#include <set>
#include <queue>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);i++)
#define INF 10000001

vector<int> adj[302];
int prev1[302];
int next1[302];
bool visited[302];
int N,K;
// augmenting path - maximal matching
bool DFS(int s)
{
	if(visited[s])
		return false;
	visited[s] = true;

	for(int i= 0; i<adj[s].size(); i++ )
	{
		if(prev1[adj[s][i]]==-1 || DFS(prev1[adj[s][i]]))
		{
			next1[s]=adj[s][i]; prev1[adj[s][i]] = s;
			return true;
		}
	}
	return false;
}
//https://www.hackerrank.com/challenges/problem-solving
int main () 
{
	int T; cin>>T;
	while(T--)
	{
		cin>>N>>K;
		memset(prev1,-1, sizeof(prev1));
		memset(next1,-1, sizeof(next1));
		vector<int> vt;	
		FOR(i,0,N)
		{
			int x; cin>>x;
			vt.push_back(x);				
		}
		FOR(i,0,vt.size())
		{
			adj[i].clear();
			FOR(j,i+1,vt.size())
				if(abs(vt[i]-vt[j]) >= K)
					adj[i].push_back(j);
		}
		int res=0;
		FOR(i,0,N)
		{
			if(next1[i]==-1)
			{
				memset(visited,0, sizeof(visited));
				DFS(i); 
			}
		}
		FOR(i,0,N)
			if(prev1[i]==-1)
				res++;
		cout<<res<<"\n";
	}

		return 0;
}
