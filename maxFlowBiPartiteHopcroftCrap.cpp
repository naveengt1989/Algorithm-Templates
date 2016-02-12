
///////////////////////////////////// 

// File Name :

// Purpose :

// Creation Date : 12-12-2014

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
using namespace std;
#define ULL  unsigned long long
#define NIL  0
#define INF INT_MAX  
int N,M,K;
int iter;

struct Node
{
	ULL distance;
	int biker;
	int bike;
	Node(ULL a, int b, int c)
	{
		distance = a;	
		biker = b;
		bike = c;
	}
	Node()
	{
	}
	bool operator<(const Node& x) const
	{
		return distance < x.distance;
	}
};

bool bfs(vector<int>& match, vector<int>& dist, vector<vector<int> >& graph) {
	int i, u, v, len;
	queue< int > Q;
	for(i=1; i<=N; i++) {
		if(match[i]==NIL) {
			dist[i] = 0;
			Q.push(i);
		}
		else dist[i] = INF;
	}
	dist[NIL] = INF;
	while(!Q.empty()) {
		u = Q.front(); Q.pop();
		// optimization
		if(dist[u]>= dist[NIL])// shortest augmenting path already found
			return true;
		//////////////
		if(u!=NIL) {
			len = graph[u].size();
			for(i=0; i<len; i++) {
				v = graph[u][i];
				if(dist[match[v]]==INF) {
					dist[match[v]] = dist[u] + 1;
					Q.push(match[v]);
				}
			}
		}
	}
	return (dist[NIL]!=INF);
}

bool dfs(int u, vector<int>& match, vector<int>& dist, vector<vector<int> >& graph) {
	int i, v, len;
	if(u!=NIL) {
		len = graph[u].size();
		for(i=0; i<len; i++) {
			v = graph[u][i];
			if(dist[match[v]]==dist[u]+1) {
				if(dfs(match[v], match, dist, graph)) {
					match[v] = u;
					match[u] = v;
					return true;
				}
			}
		}
		dist[u] = INF;
		return false;
	}
	return true;
}

int hopcroft_karp(vector<vector<int> >& graph) 
{
	int matching = 0, i;
	vector<int> match(N+M+1,NIL);
	vector<int> dist(N+M+1);
	// match[] is assumed NIL for all vertex in G
	while(bfs(match, dist, graph))
		for(i=1; i<=N; i++)
			if(match[i]==NIL && dfs(i, match, dist, graph))
				matching++;
	return matching;
}

bool satisfy(vector<Node>& dist, ULL mid)
{
	// form graph
	vector<vector<int> > graph(N+M+1);	
	// N vertices -> M vertices
	
	for(int i=0; i<mid; i++)
	{
		graph[dist[i].biker+1].push_back(dist[i].bike+N+1);
	}
	
	if(hopcroft_karp(graph) >=K)
		return true;
	else
		return false; 
}



int main()
{

	cin>>N>>M>>K;
	vector<pair<int, int> > bikers(N);
	vector<pair<int, int> > bikes(M);
	int i=0;
	while(i<N)
	{
		cin>>bikers[i].first>>bikers[i].second; i++;
	}	
	i=0;
	while(i<M)
	{
		cin>>bikes[i].first>>bikes[i].second; i++;
	}	
	vector<Node> dist;	
	for(int i=0; i< N ;i++)
	{
		for(int j=0; j< M; j++)
		{
			ULL dist_x = pow(bikers[i].first-bikes[j].first,2);
			ULL dist_y = pow(bikers[i].second-bikes[j].second,2);
			dist.push_back(Node(dist_x+dist_y,i ,j ));
		}
	}
	sort(dist.begin(), dist.end());
	ULL low =1;
	ULL high = dist.size();
	//ULL high = 227261697;
	int res=INT_MIN;
	while(low<=high)
	{
		ULL mid = low + (high-low)/2;
		//cout<<"Trying "<<mid<<"\n";
		if(satisfy(dist, mid))	
		{
			if(mid< res)
				res = mid;
			high = mid-1;	
		}
		else
		{
			low = mid+1;
		}
	}
	cout<<dist[res-1].distance<<"\n";
	return 0;
}






