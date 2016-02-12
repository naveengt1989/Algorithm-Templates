#include <bits/stdc++.h>
using namespace std;
#define MAX 50009
#define PB push_back
#define MP make_pair
int rank[20][MAX];
struct tuple
{
	int pos;
	int firstHalf,secondHalf;
};
bool compare(const tuple &a , const tuple &b)
{
	return a.firstHalf == b.firstHalf ?a.secondHalf < b.secondHalf :a.firstHalf < b.firstHalf;
}

// O(N(logN)^2)
int * suffix_array(tuple t[] , char s[], int length )
{
	int pos = 0;
	int *arr = (int*)calloc(length+9,sizeof(int));
	for(int i=0;i<length;i++)
		rank[0][i] = s[i] - 'A';// rank[i][j] is rank of sequence of length 2^i starting at index j.
	for(int cnt = 1,stp = 1;(cnt>>1) < length ; cnt<<=1,stp++)// current length is cnt or 2^stp
	{
		for(int i = 0;i<length ; i++)
		{
			t[i].firstHalf = rank[stp-1][i];// rank of 1st half starting at i of length 2^(stp-1)
			t[i].secondHalf = i+cnt < length ? rank[stp-1][i+cnt] : -1;// if beginning of second half is past length, then assign rank -1
			t[i].pos = i;//storing starting location of suffix of length 2^i

		}
		sort(t,t+length,compare);
		int rnk = 0;
		for(int i = 0 ; i<length ; i++)
		{
			if((i > 0) && (t[i-1].firstHalf == t[i].firstHalf && t[i].secondHalf == t[i-1].secondHalf))
				rnk = rank[stp][t[i-1].pos];
			else
				rnk = i;
			rank[stp][t[i].pos] = rnk;
		}
	}
	pos = ceil(log(length)/log(2));
	for(int i=0;i<length;i++)
		arr[rank[pos][i]] = i;// return all suffixes sorted
	return arr;
}
int LCP(int i,int j,int n)
{
	int res = 0;
	if(i==j)
		return n - i;
	for(int stp = ceil(log(n)/log(2)) ; stp>=0 && i < n && j < n ; stp--)
		if(rank[stp][i] == rank[stp][j])
		{
			res += 1<<stp;
			i += 1<<stp;
			j += 1<<stp;
		}
	return res;
}
int LCParray(char s[],int p[],int n)
{
	int sum = 0;
	for(int i = 1 ; i < n ; i++)
		sum += (LCP(p[i-1],p[i],n));
	return sum;
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		char s[50009];
		scanf("%s",s);
		int n = strlen(s);
		tuple t[n + 9];
		int *p;
		p = suffix_array(t,s,n);
		long long lcp_sum = 0,suffix_sum = 0;
		lcp_sum = LCParray(s,p,n);
		for(int i=0;i<n;i++)
			suffix_sum += p[i];
		printf("%lld\n",(long long)n*n - lcp_sum - suffix_sum);
		printf("%lld\n",(long long)n*(n+1)/2 - lcp_sum);
	}
	return 0;
}
