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
int N,T,M;


bool bfs(vector<vector<int> >& rGraph, int s, int t, int parent[])
{
    // Create a visited array and mark all vertices as not visited
	int V = 2*N+2;
    vector<bool> visited(V,0);
    //memset(visited, 0, sizeof(visited));
 
    // Create a queue, enqueue source vertex and mark source vertex
    // as visited
    queue <int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;
 
    // Standard BFS Loop
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
 
        for (int v=0; v<V; v++)
        {
            if (visited[v]==false && rGraph[u][v] > 0)
            {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
 
    // If we reached sink in BFS starting from source, then return
    // true, else false
    return (visited[t] == true);
}
 
// Returns tne maximum flow from s to t in the given graph
int fordFulkerson(vector<vector<int> >& graph, int s, int t)
{
    int u, v;
 
    // Create a residual graph and fill the residual graph with
    // given capacities in the original graph as residual capacities
    // in residual graph
	int V = 2*N+2;
    vector<vector<int> > rGraph(V, vector<int>(V,0)); // Residual graph where rGraph[i][j] indicates 
                     // residual capacity of edge from i to j (if there
                     // is an edge. If rGraph[i][j] is 0, then there is not)  
    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
             rGraph[u][v] = graph[u][v];
 
    int parent[V];  // This array is filled by BFS and to store path
 
    int max_flow = 0;  // There is no flow initially
 
    // Augment the flow while tere is path from source to sink
    while (bfs(rGraph, s, t, parent))
    {
        // Find minimum residual capacity of the edhes along the
        // path filled by BFS. Or we can say find the maximum flow
        // through the path found.
        int path_flow = INT_MAX;
        for (v=t; v!=s; v=parent[v])
        {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }
 
        // update residual capacities of the edges and reverse edges
        // along the path
        for (v=t; v != s; v=parent[v])
        {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
 
        // Add path flow to overall flow
        max_flow += path_flow;
    }
 
    // Return the overall flow
    return max_flow;
}

int main () 
{
	int C;
	vector<int> res;
	cin>>C;
	while(C--)
	{
		cin>>N>>T>>M;
		vector<vector<int> > graph(2*N+2, vector<int>(2*N+2,0));
		vector<int> degree(N+1,0);
		// source=0, sink = 2*N+1
		int i=0;
		while(i<M)
		{
			int j,k;
			cin>>j>>k;	
			graph[j][N+k]=1;
			//graph[N*k+1][j]=1;
			graph[k][N+j]=1;
			degree[j]++;degree[k]++;
			//graph[N*j+1][k]=1;
			i++;
		}
		// add source-A, B-sink edges
		for(i=1; i<=N; i++)
		{
			graph[0][i] =min(T,degree[i]);
			graph[N+i][2*N+1]=1;
		}	
		res.push_back(fordFulkerson(graph, 0, 2*N+1));
	}

	for(int i=0; i< res.size(); i++)
	{
		cout<<res[i]<<"\n";
		
	}
return 0;
}
