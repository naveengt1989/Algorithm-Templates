
///////////////////////////////////// 

// File Name :

// Purpose :

// Creation Date : 27-02-2016

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
	int sum;
	Node()
	{
		sum=0; 
	}
};

const int N=10;// array limit
Node tree[N<<1];
int n;
Node merge(Node& x, Node& y)
{
	Node ret;
	ret.sum += x.sum + y.sum;	
	return ret;
}

// point update
void upd(int ind, int val)
{
	ind += n;// go to leaf
	tree[ind].sum += val;
	while(ind>1)
	{
		ind >>= 1;// go to parent 
		tree[ind] = merge(tree[2*ind], tree[2*ind+1]); 
	}
}

int query(int l, int r, int value)
{
	l += n; r += n;
	int ret=0;
	while(l<=r)						
	{
		if(l&1)	ret += tree[l].sum;
		if(!(r&1))	ret += tree[r].sum;
		l = (l+1)>>1; // go to upper layer
		r = (r-1)>>1; // go to upper layer
	}
	return ret;
}


void build()
{
	for(int j=n-1; j>=1; j--)// non leaf nodes start at index: n-1 and continue uptill 1
		tree[j] = merge(tree[2*j], tree[2*j+1]);
}

int main()
{
	int i=0;	
	cin>>n;
	while(i < n)
	{
		int x; cin>>x;
		tree[n+i].sum = x;
		i++;
	}
	build();
	upd(2,1);// upd(index, increment)
	cout<<query(2,4);// query(l_index, r_index)
	return 0;
}


