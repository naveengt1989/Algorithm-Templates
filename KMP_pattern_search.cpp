
///////////////////////////////////// 

// File Name :

// Purpose :

// Creation Date : 10-04-2016

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
#define LL unsigned long long
#define ULL unsigned long long
#define FOR(i,a,b) for(int i=a; i<b; i++)
#define f first
#define s second
#define pb push_back

// KMP 
bool search(std::string& text, std::string& pattern)
{
	std::string str = pattern+"$"+text;
	std::vector<int> lps(str.length(),0); 
	int len=0;int cur=1;int res=0;
	while(cur<str.length())
	{
		while(len>0 && str[len]!=str[cur])	len = lps[len-1];
		if(str[len]==str[cur])	len++;
		lps[cur++]= len;
		res = std::max(lps[cur-1],res);
	}	
	if(res==pattern.length())	{return true;}
	else						{return false;}
}

int main()
{
	string text="ananan";
	string pattern="ana";
	if(search(text,pattern))	cout<<pattern<<" found in: "<<text<<"\n";
	else						cout<<pattern<<" NOT found in: "<<text<<"\n";
}


