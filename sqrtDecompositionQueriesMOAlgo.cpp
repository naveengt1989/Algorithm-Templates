
///////////////////////////////////// 

// File Name :

// Purpose :

// Creation Date : 21-02-2016

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
int N;int root_N;
struct query
{
	int lt;
	int rt;
	int index;
	query(int a, int b, int c)	
	{
		lt=a;	
		rt=b;
		index=c;
	}
	bool operator<(const query& x) const
	{
		if(lt/root_N < x.lt/root_N)				
			return true;
		else if(lt/root_N == x.lt/root_N && rt < x.rt)
			return true;
		else
			return false;
	}
};
int cnt[1000002];
int cur;
void add(int x)
{
	cnt[x]++;
	if(cnt[x]==1)
		cur++;	
}
void del(int x)
{
	cnt[x]--;
	if(cnt[x]==0)
		cur--;	
}
// http://www.spoj.com/submit/DQUERY/
// MO algorithm
int main()
{
	inp(N); root_N = sqrt(N);	
	vector<int> vt;
	int i=0;
	while(i<N)
	{
		int x; inp(x);
		vt.push_back(x);
		i++;
	}
	int Q; inp(Q);	
	vector<query> qt;
	i=0;	
	while(i<Q)
	{
		int left; int right;inp(left);inp(right); 
		qt.push_back(query(left-1, right-1,i));
		i++;
	}
	sort(qt.begin(), qt.end());
	int l=0; int r=0;add(vt[0]);
	vector<int> res(Q,-1);
	for(int i=0; i< qt.size(); i++)
	{
		while(l<qt[i].lt)
		{
			del(vt[l]); l++;
		}
		while(l>qt[i].lt)
		{
			l--; add(vt[l]);
		}
		while(r<qt[i].rt)
		{
			r++; add(vt[r]); 
		}
		while(r>qt[i].rt)
		{
			del(vt[r]); r--;
		}
		res[qt[i].index] = cur;
	}		
	for(auto it: res)	
		printf("%d\n",it);
		
	return 0;
}


