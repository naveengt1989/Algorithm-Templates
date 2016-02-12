
///////////////////////////////////// 

// File Name :

// Purpose :

// Creation Date : 03-09-2015

// Last Modified : <modified_date>

// Created By : Naveen Thomas 

//////////////////////////////////////

#include <bits/stdc++.h>
using namespace std;
#define CLOCK_START double start_t = clock();
#define CLOCK_STOP cout << "Took: " << ((clock() - start_t) / CLOCKS_PER_SEC);
#define FOR(i,a,b) for(int i=a; i<b; i++)
#define LL long long
#define vi vector<int>
#define vvi vector<vi>
#define vii vector<ii>
#define CLR(a, x) memset( a, x, sizeof( a ) )
#define ULL long long
#define MOD 1000000007

#define ii pair<int,int>
struct Node
{
	string id;
	string parent;
	string text;
	int depth;
	int time;
	bool finish;
	Node(string a, string b, string c, int d, int e, bool f)
	{
		id=a; parent =b;text=c; depth=d;time=e;finish=f;
	}
	bool operator<(const Node& x)const
	{
		if(depth < x.depth)	
			return true;
		else if(depth == x.depth && time<= x.depth)
			return true;
		else
			return false;
	}
}

int main()
{
	//int N; scanf("%d\n",&N);
	string str;
	//// delmiter code ////	
	while(getline(cin,str))
	{
		 // input with spaces
		stringstream ss(str);
		string token; int j=0;
		while(getline(ss, token,','))
		{
			if(j==4)
			{
				// string to integer
				int x = stoi(token);
				// integer to string
				stringstream st; st<<x;
				string f = st.str();
				cout<<x<<" "<<f<<"\n";	
			}
			else
				cout<<token<<"\n";	
			j++;
		}
	}
	/////////////////////////
	
	return 0;
}







