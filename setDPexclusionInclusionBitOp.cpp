#include<bits/stdc++.h>
#define MOD 1000000007
#define LLD long long int
#define si(x) scanf("%d",&x);
#define MAXV 1048576
using namespace std;
char str[100];
int p[MAXV+3];
int mp[MAXV+3];
//https://www.hackerrank.com/contests/w16/challenges/vim-war/editorial
int main() {
	p[0] = 1;
	for(int i=1;i<=MAXV;i++)
		p[i] = (p[i-1]*2)%MOD;
	for(int i=0;i<=MAXV;i++)
	{
		p[i]--;
		p[i] += MOD;
		p[i] %= MOD;
	}
	int n, m, t=1, x;
	while(t--) {
		memset(mp,0,sizeof mp);
		si(n);
		si(m);
		for(int i=0;i<n;i++) {
			int val = 0;
			scanf("%s",str);
			for(int j=0;j<m;j++) {
				x = str[j]-'0';
				val = val*2 + x;
			}
			mp[val]++;
		}

		int req = 0;
		scanf("%s",str);
		for(int j=0;j<m;j++) {
			x = str[j]-'0';
			req = req*2 + x;
		}

		for(int i=0;i<20;i++)// for each bit
			for(int j=0; j<=MAXV; j++) {// update each number in range
				if(j&(1<<i)) {// is bit i set in j
					mp[j] += mp[j^(1<<i)];// unset bit i in j and add count in that number to j
				}
			}
		int ans = 0;
		for(int j=req; j>=0; j--) {
			if((j|req)!=req)
				continue;
			if(__builtin_popcount(j^req)%2)
				ans = (ans - p[mp[j]] + MOD)%MOD;
			else
				ans = (ans + p[mp[j]])%MOD;
		}
		cout<<ans<<endl;
	}

}
