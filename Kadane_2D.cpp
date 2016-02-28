
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
#define vvi vector<vi>
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
int M,N;
int kadane(int l,int h, vvi& sum)
{
	int mx=sum[h][1]-sum[l-1][1]; int mx_total=sum[h][1]-sum[l-1][1];
	FOR(i,2,N+1)	
	{
		mx = max(mx+sum[h][i]-sum[l-1][i] ,sum[h][i]-sum[l-1][i]);
		mx_total = max(mx_total,mx);
	}
	return mx_total;
}

int main()
{
	cin>>M>>N;
	vvi sum(M+1, vi(N+1,0));
	FOR(i,1,M+1)	
	{
		FOR(j,1,N+1)	
		{
			int x; cin>>x;
			sum[i][j] = sum[i-1][j]+ x;
		}
	}
	int res= INT_MIN;	
	FOR(i,1,M+1)	
	{
		FOR(j,i,M+1)	
		{
			res = max(res, kadane(i,j,sum));	
		}
	}
	cout<<res<<"\n";
	return 0;
}


