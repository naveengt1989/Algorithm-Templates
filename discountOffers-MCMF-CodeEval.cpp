
///////////////////////////////////// 

// File Name :

// Purpose :

// Creation Date : 12-02-2016

// Last Modified : <modified_date>

// Created By : Naveen Thomas 

//////////////////////////////////////
#include <bits/stdc++.h>

using namespace std;
#define CLOCK_START double start_t = clock();
#define CLOCK_STOP cout << "Took: " << ((clock() - start_t) / CLOCKS_PER_SEC);
#define FOR(i,a,b) for(int i=a; i<b; i++)
#define ii pair<int,int>
#define vi vector<int>
#define CLR(a, x) memset( a, x, sizeof( a ) )
#define LL long long
#define ULL unsigned long long
const int N = 110, inf = 1000000010;


struct Edge
{
	// b = adjacent vertex, c = cost per unit flow, u = capacity, f = current flow, back = id of back edge in adjacent vertex
	int b, u, f, back;
	double c;
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
		void addEdge(int a, int b, double c, int u)
		{
			Edge e1 = {b, u, 0, (int)g[b].size(), c};// forward edge
			Edge e2 = {a,  0, 0, (int)g[a].size(), -c};// back edge(cost is negative on removing flow thru back edge, cost is corr. reduced)
			g[a].push_back(e1);
			g[b].push_back(e2);
		}

		double minCostMaxFlow()
		{
			int flow = 0;
			double cost = 0;
			int *state = new int[n];
			int *from = new int[n];
			int *from_edge = new int[n];
			double *d = new double[n];
			int *q = new int[n];
			int qh, qt;
			qh = 0, qt = 0;
			while (true)
			{
				for (int i = 0; i < n; i++) state[i] = 2, d[i] = inf;
				fill(from, from + n, -1);// from[i]= state fom where i was reached
				state[s] = 1;
				// state[x]=0(not visited) state[x]=1(in Q) state[x]=2(visited)
				q[qh++] = s;// add state src(0) to Q
				d[s] = 0;// update distance of 1st vertex to 1
				// Djikstra algorithm for negative edges(exponential complexity)
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
				//cout<<d[t]<<" "<<inf<<"\n";
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
int n, m, q;

struct customer
{
	int len;
	int cons; int vow;
	customer(int a, int b,int c)
	{
		len =a; cons=b; vow=c;
	}
	void print()
	{cout<<"LEN="<<len<<"consonants="<<cons<<"vow="<<vow<<"\n";}
};
int gcd(int a, int b)
{
	if(b>a)
		swap(a,b);
	if(b==0)
		return a;

	return gcd(a%b,b);
}
double calc(customer a, int prod)
{
	double res;
	if((prod&1)==0)
		res = a.vow*1.5;
	else
		res = a.cons;
	if(gcd(prod, a.len)!=1)
		res *= 1.5;
	return res;
}

void proc( char* file)
{
	string str; set<char> v; 
	v.insert('A');v.insert('E');v.insert('I');v.insert('O');v.insert('U'); v.insert('Y');
	v.insert('a');v.insert('e');v.insert('i');v.insert('o');v.insert('u'); v.insert('y');
	ifstream stream(file);

	while(getline(stream, str))
	{
		if(str.length()==0)
			continue;
		vector<int> prod_lens; vector<customer> custs;
		//cout<<str<<"\n";
		int len=0; int vowels=0; int cons=0; int i;
		for(i=0; i< str.length(); i++)
		{
			if(str[i]==';')
			{
				custs.push_back(customer(len, cons, vowels));len=0; vowels=0; cons=0;i++;
				break;
			}
			else if(str[i]==',')
			{
				custs.push_back(customer(len, cons, vowels));len=0; vowels=0; cons=0;
				len=0; vowels=0; cons=0;
			}
			else
			{
				if(v.find(str[i])!= v.end())
				{	vowels++;len++;}
				else if((str[i]>='A' && str[i]<='Z') || (str[i]>='a'&&str[i]<='z'))	
				{	cons++;len++;}
			}
		}
		for(;i< str.length(); i++)
		{
			if(str[i]==',')
			{
				prod_lens.push_back(len); len=0;
			}	
			else if((str[i]>='A' && str[i]<='Z') || (str[i]>='a'&&str[i]<='z'))
				len++;
		}
		if(len!=0)
			prod_lens.push_back(len);
		/*for(auto it: prod_lens)
			cout<<it<<"\n";
		for(auto it: custs)
			it.print();*/
		// MCMF algo
		n = custs.size(); m =  prod_lens.size(); 
		MCMF t(0, n+m+1, n + m+2);
		for (int i = 1; i <= n; i++) 
			t.addEdge(0, i, 0, 1);
		for (int i = 1; i <= m; i++) 
			t.addEdge(n+i, n+m+1, 0, 1);
		for(int i=0; i< n; i++)
		{
			for(int j=0; j<m; j++)
			{
				double wt = calc(custs[i], prod_lens[j]);	
				t.addEdge(i+1, j+n+1, -wt, 1);
				//cout<<wt<<" ";
			}
			//cout<<"\n";
		}
		printf("%.2f\n", -t.minCostMaxFlow());
	}
}

int main(int argc, char *argv[]) 
{
	proc(argv[1]);
	
	return 0;
} 
