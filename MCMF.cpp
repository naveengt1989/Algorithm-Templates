#include <cstdio>
#include <vector>

using namespace std;

const int N = 110, inf = 1000000010;


struct Edge
{
	// b = adjacent vertex, c = cost per unit flow, u = capacity, f = current flow, back = id of back edge in adjacent vertex
	int b, c, u, f, back;
};

class MCMF
{
	private:
		// s=source, t=target, n=number of vertices
		int s, t, n;
		vector<Edge> g[N];

	public:

		MCMF(int _s, int _t, int _n)
		{
			s = _s;
			t = _t;
			n = _n;
		}

		// a = 1st vertex, b= 2nd vertex, c = cost per unit, u = capacity
		void addEdge(int a, int b, int c, int u)
		{
			Edge e1 = {b, c, u, 0, g[b].size()};// forward edge
			Edge e2 = {a, -c, 0, 0, g[a].size()};// back edge(cost is negative on removing flow thru back edge, cost is corr. reduced). Initially cost is reduced
			g[a].push_back(e1);
			g[b].push_back(e2);
		}

		int minCostMaxFlow()
		{
			int flow = 0;
			int cost = 0;
			int *state = new int[n];
			int *from = new int[n];
			int *from_edge = new int[n];
			int *d = new int[n];
			int *q = new int[n];
			int qh, qt;
			while (true)
			{
				qh = 0, qt = 0;
				for (int i = 0; i < n; i++) state[i] = 2, d[i] = inf;
				fill(from, from + n, -1);// from[i]= state fom where i was reached
				state[s] = 1;
				// state[x]=0(not visited) state[x]=1(in Q) state[x]=2(visited)
				q[qh++] = s;// add state src(0) to Q
				d[s] = 0;// update distance of 1st vertex to 1
				// SPFA algorithm for negative edges(worst case complexity: O(EV))
				while (qh != qt)// Q becomes empty
				{
					int v = q[qt++];// pop current vertex
					qt %= n;//update tail index
					state[v] = 0; // make state: v as visited
					// if current outflow(of adjacent vertex) < Total outflow capacity(of adjacent vertex)
					// && cost_distance[adj. vertex] > cost_distance[curent vertex] + cost of edge 
					for (int i = 0; i < g[v].size(); i++) if (g[v][i].f < g[v][i].u && d[g[v][i].b] > d[v] + g[v][i].c)
					{
						int to = g[v][i].b;// to = adjacent vertex
						d[to] = d[v] + g[v][i].c;// setting cost_distance of adjacent vertex
						from[to] = v; // setting parent of adjacent vertex to v
						from_edge[to] = i;// setting which edge to to is selected
						if (state[to] == 1) continue;// to is already in Q. So just update distance
						if (!state[to])//re-insert vertex at tail....already processed vertex
						{
							qt--;
							if (qt == -1) qt = n - 1;
							q[qt] = to;
							state[to] = 1;
						} else
						{// new vertex
							state[to] = 1;
							q[qh++] = to;
							qh %= n;
						}
					}
				}
				if (d[t] == inf) break;
				int it = t;
				int addflow = inf;
				while (it != s)
				{
					// find minimum add flow in shortest path found
					addflow = min(addflow, g[from[it]][from_edge[it]].u - g[from[it]][from_edge[it]].f);
					it = from[it];
				}
				it = t;
				while (it != s)
				{
					// edge = from --> to
					g[from[it]][from_edge[it]].f += addflow;//add to current flow of from vertex of current edge
					// in following step by decrementing from current flow, residual capacity(u-f) in back edge is increased.
					g[it][g[from[it]][from_edge[it]].back].f -= addflow; // subtract from current flow in back edge of to vertex
					cost += g[from[it]][from_edge[it]].c * addflow;// add to total cost(min flow * cost_per_unit)
					it = from[it];
				}
				flow += addflow;
			}
			return cost;
		} 
};

struct Node
{
	int val;
	int end;
	int cost;
	Node(int a, int b, int c)
	{
		val=a; end=b; cost=c;
	}
	bool operator<(const Node& x)const
	{
		if(a< x.a)
			return true;
		else if(a==x.a && end==0)
			return true;
		else
			return false;
	}
};
int n, k;
int main()
{
	scanf("%d %d", &n, &k);
	int i=0; multiset<Node> ends;
	while(i< n)
	{
		int x,y,c; cin>>x>>y>>c;
		ends.insert(Node(x,0,c)); ends.insert(Node(y,1,c));
		i++;
	}
	MCMF t(0, ends.size()+1, ends.size() + 2);
	for (auto it = ends.begin(), int i=1; it != ends.end(); it++, i++) 
	{
		if(it->end > 1)
			t.addEdge(i-1, i, 0, k);
		if(it->end==0)
			t.addEdge(0, i, -it->second, 1);
		else
			t.addEdge(i,ends.size()+1, 0, 1);
	}

	// maximum flow, return minimum cost => t.minCostMaxFlow
	printf("%d\n", -t.minCostMaxFlow());
	return 0;
}


