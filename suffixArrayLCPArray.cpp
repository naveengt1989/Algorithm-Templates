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
int * suffix_array(tuple t[] , string& s, int length )
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
int LCParray(string s,int p[],int n)
{
	int sum = 0;
	for(int i = 1 ; i < n ; i++)
		sum += (LCP(p[i-1],p[i],n));
	return sum;
}

//  http://codeforces.com/blog/entry/12796
//	LCP(i,j) = Min(LCP(i)...LCP(j-1));
vector<int> kasai_lcparray(string& s, int* sa)
{
    int n=s.length(),k=0;
    vector<int> lcp(n,0);
    vector<int> rank(n,0);

    for(int i=0; i<n; i++) rank[sa[i]]=i;

    for(int i=0; i<n; i++, k?k--:0)
    {
        if(rank[i]==n-1) {k=0; continue;}
        int j=sa[rank[i]+1];
        while(i+k<n && j+k<n && s[i+k]==s[j+k]) k++;
        lcp[rank[i]]=k;
    }
    return lcp;
}
//LCP(i,j) = Min(LCP(i)...LCP(j-1));

void print_lcp(string& s, vector<int>& lcp, int *sa )
{
	for(int i=0; i< lcp.size(); i++)
		cout<<s.substr(sa[i])<<" "<<lcp[i]<<"\n";
}

void print_suffixArray(string& s, int* sa)
{
	for(int i=0; i< s.length(); i++)
		cout<<sa[i]<<" "<<s.substr(sa[i])<<"\n";

}

int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		string s;
		cin>>s;
		int n = s.length();
		tuple t[n + 9];
		int *sa;
		sa = suffix_array(t,s,n);
		// obtain lcp array
		vector<int> lcp = kasai_lcparray(s,sa);
		long long lcp_sum = 0,suffix_sum = 0;
		lcp_sum = LCParray(s,sa,n); 
		//print_lcp(s, lcp, sa); 
		print_suffixArray(s,sa);
		
		for(int i=0;i<n;i++)
			suffix_sum += sa[i];
		printf("%lld\n",(long long)n*n - lcp_sum - suffix_sum);
		printf("%lld\n",(long long)n*(n+1)/2 - lcp_sum);
	}
	return 0;
}



