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
#include <bitset>
#include <ctime>        
#include <sys/time.h>
#include<iomanip>
#include<math.h>

using namespace std;
#define ULL unsigned long long 
#define P 1000000007 
struct subset
{
	int parent;
	int rank;
	subset()
	{
		parent =-1;
		rank=-1;
	}	
};

int Find(vector<subset>& nodes, int i)
{
    if (nodes[i].parent != i)
        nodes[i].parent = Find(nodes, nodes[i].parent);
 
    return nodes[i].parent;
}

void Union(vector<subset>& nodes, int x, int y)
{
	int xroot  = Find(nodes, x);
	int yroot  = Find(nodes, y);
	//cout<<"Union: "<<x<<" "<<y<<" Roots: "<<xroot<<" "<<yroot<<"\n";
	if(xroot == yroot)
		return;
	if (nodes[xroot].rank < nodes[yroot].rank)
		nodes[xroot].parent = yroot;
	else if (nodes[xroot].rank > nodes[yroot].rank)
		nodes[yroot].parent = xroot;
	else
	{
		nodes[yroot].parent = xroot;
		nodes[xroot].rank++;
	}
}

void print(vector<subset>& nodes)
{
	cout<<"#########################################\n";
	for(int i=0; i< nodes.size(); i++)
	{
		cout<<"Node: "<<i<<" Parent: "<<nodes[i].parent<<" Rank: "<<nodes[i].rank<<"\n";
	}
	cout<<"#########################################\n";
}

int main() 
{
	ULL res=0;

	ULL N,L;
	cin>>N>>L;
	vector<vector<int> > adj(N, vector<int>());
	vector<subset> nodes(N);
	for(int i=0; i< N; i++)
	{
		nodes[i].parent=i;
		nodes[i].rank=0;
	}
	//print(nodes);
	while(L--)
	{
		int x,y;
		cin>>x>>y;
		Union(nodes, x,y);			
		//print(nodes);
	}
	map<int, int> groups;	
	for(int i=0; i< N; i++)
	{
		int parent = Find(nodes,i);
		//cout<<" Node: "<<i<<" parent: "<<parent<<"\n";
		map<int, int>::iterator it = groups.find(parent);
		if(it==groups.end())
		{
			groups.insert(make_pair(parent, 1));	
		}
		else
		{
			it->second++;
		}
	}
	res = (N*(N-1))/2;
	for(map<int, int>::iterator it = groups.begin(); it!= groups.end(); it++)
	{
		//cout<<"group: "<<count<<" = "<<it->second<<"\n";
		int n = it->second;
		res -= n*(n-1)/2;	
	}		
	cout<<res<<"\n";
	return 0;
}

//T(n) = T(n-1) + T(n-4)
