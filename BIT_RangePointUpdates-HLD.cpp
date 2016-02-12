
///////////////////////////////////// 

// File Name :

// Purpose :

// Creation Date : 26-06-2015

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
#define CLR(a, x) memset( a, x, sizeof( a ) )
#define FOR(i,a,b) for(int i=a; i<b; i++)
using namespace std;
#define vi vector<int> 
#define vvi vector<vi> 
#define ii pair<int, int> 
#define vii vector<ii>
#define getcx getchar_unlocked
#define ULL unsigned long long
#define LL  long long
#define TLL  LL
#define P 1000000009


int N,S,M;
int intersection[500][100002];
int present[500][100002];
int A[100002];
int T[330];
int B[330];
//int B[100002];
inline void inp( int &n )//fast input function
{
	n=0;
	int ch=getcx();ULL sign=1; 
	while( ch < '0' || ch > '9' ){if(ch=='-')sign=-1; ch=getcx();}

	while( ch >= '0' && ch <= '9' )
		n = (n<<3)+(n<<1) + ch-'0', ch=getcx();
	n=n*sign;
}
TLL* tree1;
TLL* tree2;
TLL* tree3;
int BIT_MAX;
void update(TLL* tree, int x, LL val)
{
	while (x <= BIT_MAX)
	{
		tree[x] += (val+P)%P;
		tree[x] %= P;
		x += (x & -x); 
	}
}

void updateRangeBIT(int x, int y, TLL val)
{
	update(tree1, x, val); 	
	update(tree1, y + 1, -val) ;
	update(tree2, x, val * (x-1));
	update(tree2, y + 1, -val * y);// to compensate for lack of val*y in tree1
}
LL read(TLL* tree, int idx)
{
	LL sum = 0;
	while (idx > 0)
	{
		sum += (tree[idx]+P)%P;
		sum %= P;
		idx -= (idx & -idx);
	}
	return sum;
}

TLL readPointBIT(int idx)
{
	return read(tree1, idx)%P;
}

LL readRange(int idx)
{
	//cout<<"Till Point : "<<idx<<"  "<<read(tree1, idx) * idx<<" "<<read(tree2, idx)<<"\n";
	return ((read(tree1, idx) * idx)%P - read(tree2, idx)%P + P)%P;
}

LL readRangeBIT(int idx, int idy)
{
	//cout<<readRange(idx-1)<<" "<<readRange(idy)<<"\n";
	
	return (readRange(idy)  - readRange(idx-1)+ P)%P;
}
void initBIT(int N)
{
	tree1  =  new TLL[N+1];
	tree2  =  new TLL[N+1];
	tree3  =  new TLL[N+1];
	BIT_MAX=N;
	memset(tree1, 0, sizeof(TLL)*(N+1));
	memset(tree2, 0, sizeof(TLL)*(N+1));
	memset(tree3, 0, sizeof(TLL)*(N+1));
}

// https://www.hackerrank.com/contests/epiccode/challenges/set-queries
int main()
{
	inp(N); inp(S); inp(M);
	vvi input(S);
	int K = max(sqrt(N)-75, sqrt(N));
	initBIT(N);
	vi heavy(S,-1); int h_id=-1;	
	FOR(i,0,S)	
	{
		int size; inp(size); 	
		if(size > K)
		{
			h_id++;
			heavy[i] = h_id;	
		}
		FOR(j,0,size)
		{
			int x; inp(x);
			input[i].push_back(x);
			if(size > K)
			{
				present[h_id][x]++;
			}
		}	
	}
	//vi T(h_id+1, 0);
	//vi B(h_id+1, 0);
	// find intersection
	FOR(i,0,S)	
	{
		FOR(k,0, h_id+1)
		{
			FOR(j,0,input[i].size())
			{
				if(heavy[i] == k)	
					break;
				if(present[k][input[i][j]])
					intersection [k][i]++; 	
			}
		}
	}
	FOR(k,0, h_id+1)
	{
		FOR(j,2,N+1)
		{
			present [k][j] += present[k][j-1]; present[k][j] %= P;
		}
	}
	while(M--)
	{
		int a,b,c,d;
		inp(a); 
		if(a==1)
		{
			inp(b); inp(c);
			b--;
			// O(1)
			if(heavy[b] != -1)
			{
				T[heavy[b]] += c;
				T[heavy[b]] %= P;
			}
			// O(S*logN) + O(H)
			else
			{
				//cout<<"Updating set: "<<b<<" size: "<<input[b].size()<<"\n";
				FOR(j,0,input[b].size())
				{
					A[input[b][j]] += c;		
					A[input[b][j]] %= P;
					update(tree3, input[b][j], c);
				}
				//cout<<"Res: "<<read(tree3, 9) - read(tree3, 4-1)<<"\n";
				FOR(k,0, h_id+1)
				{
					//cout<<"Intersection with: Hid: "<<k<<" "<<intersection[k][b]<<"\n";
					B[k] += (1LL*intersection[k][b]*c)%P;
					B[k] %= P;
				}
			}
		}
		else if(a==2)
		{
			inp(b);
			b--;
			LL res =0;
			//O(H)
			if(heavy[b] != -1)
			{
				res += 1LL*B[heavy[b]]; res %= P;
				res += (1LL*T[heavy[b]]*input[b].size())%P; res %= P;
				FOR(k,0, h_id+1)
				{
					res += (1LL*intersection[k][b]*T[k])%P; res %= P;
				}
			}
			else
			{
				//O(logN*S)
				FOR(j,0,input[b].size())
				{
					//cout<<"Value: "<<input[b][j]<<" = "<<A[input[b][j]]<<"\n";
					//cout<<"Value: Range "<<input[b][j]<<" = "<<readRangeBIT(input[b][j], input[b][j])<<"\n";
					res += 1LL*A[input[b][j]]; res %= P;
					//res += 1LL*readRangeBIT(input[b][j], input[b][j]); res %= P;
					res += read(tree1, input[b][j]); res %= P;
				}
				FOR(k,0, h_id+1)
				{
					//cout<<"INtersection with: hid: "<<k<<" "<<intersection[k][b]<<" value: "<<T[k]<<"\n";
					res += (1LL*intersection[k][b]*T[k])%P; res %= P;
				}
			}
			printf("%lld\n", res);
		}
		else if(a==3)
		{
			inp(b); inp(c); inp(d);
			updateRangeBIT(b,c,d);
			FOR(k,0, h_id+1)
			{
				B[k] += (1LL*d*(present[k][c]-present[k][b-1] + P)%P)%P; B[k] %= P;
			}	
		}
		else
		{
			LL res =0;
			inp(b); inp(c);
			FOR(k,0, h_id+1)
			{
				//cout<<"hid: "<<k<<" "<<b-1<<" "<<c<<" "<<present[k][c]-present[k][b-1]<<" "<<T[k]<<"\n";
				res += (1LL*(present[k][c]-present[k][b-1]+P)%P * T[k])%P; res %= P;
			}
			//cout<<"Range tree: "<<readRangeBIT(b,c)<<"\n";
			res += readRangeBIT(b,c); res %= P;
			//cout<<"A tree"<<b <<" "<<c<<" "<<read(tree3, c) - read(tree3, b-1)<<"\n";
			res += 1LL*(read(tree3, c) - read(tree3, b-1) + P)%P; res %= P;
			printf("%lld\n", res);
		}
	}	
	return 0;
}


