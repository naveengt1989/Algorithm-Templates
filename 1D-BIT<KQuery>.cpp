
///////////////////////////////////// 

// File Name :

// Purpose :

// Creation Date : 18-02-2016

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
#define FOR(i,a,b) for(int i=a; i<b; i++)
#define M 30002
inline void inp( int &n )//fast input function
{
	n=0;
	unsigned int ch=getchar_unlocked();int sign=1; 
	while( ch < '0' || ch > '9' ){if(ch=='-')sign=-1; ch=getchar_unlocked();}

	while( ch >= '0' && ch <= '9' )
		n = (n<<3)+(n<<1) + ch-'0', ch=getchar_unlocked();
	n=n*sign;
}

struct Node
{
	int id;
	int	left;
	int right;
	int val;  
	bool Q;
	Node(int a, int b, int c, int d, bool e)
	{
		id=a; left=b; right=c;val=d;Q=e;
	}
	bool operator<(const Node& x)const
	{
		if(val>x.val)
			return true;
		else if(val==x.val && Q==true)
			return true;
		else
			return false;
	}
};
int tree[M+1];
void update(int x, int val)
{
	while (x <= M)
	{
		tree[x] += val;
		x += (x & -x); 
	}
}

int read(int idx)
{
	int sum = 0;
	while (idx > 0)
	{
		sum += tree[idx];
		idx -= (idx & -idx);
	}
	return sum;
}
// http://www.spoj.com/problems/KQUERY/
int main()
{
	int N; inp(N);
	vector<Node> vt;
	for(int i=0; i<N; i++)	
	{
		int x;inp(x);vt.push_back(Node(i,-1,-1,x,false));
	}
	int Q; inp(Q);
	vector<int> queries(Q,-1);
	for(int i=0; i<Q; i++)	
	{
		int l,r,x; inp(l); inp(r); inp(x);
		vt.push_back(Node(i,l,r,x,true)); 
	}

	sort(vt.begin(), vt.end());
	for(int i=0; i< vt.size(); i++)
	{
		if(vt[i].Q)		
			queries[vt[i].id] = read(vt[i].right)-read(vt[i].left-1);		
		else	
			update(vt[i].id+1,1);
	}
	for(auto it: queries)
		printf("%d\n",it);
	return 0;
}


