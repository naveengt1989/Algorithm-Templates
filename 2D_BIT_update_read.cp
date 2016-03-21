
///////////////////////////////////// 

// File Name :

// Purpose :

// Creation Date : 12-12-2014

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
#define ii pair<int,int>
#define f first
#define s second
#define M 1000
#define N 1000
using namespace std;

int tree[M+1][N+1];
void update(int x, int y, int val)
{
	int y1;
	while (x <= M)
	{
		y1 = y;
		while (y1 <= N)
		{
			tree[x][y1] += val;
			y1 += (y1 & -y1); 
		}
		x += (x & -x); 
	}
}

int read(ii inp)
{
	int idx = inp.f; int idy = inp.s;
	int sum = 0;
	int y1;
	while (idx > 0)
	{
		y1 =idy;
		while(y1 > 0)
		{
			sum += tree[idx][y1];
			y1 -= (y1 & -y1);
		}
		idx -= (idx & -idx);
	}
	return sum;
}

void printBIT()
{
	for (int i=0; i< 10; i++)
	{
		for (int j=0; j<10; j++)
		{
			cout<<read(ii(i,j))<<" ";	
		}
		cout<<"\n";
	}
}

int read(ii LL, ii UR)
{
	ii A(LL.f-1, UR.s);
	ii B=UR;
	ii C(LL.f-1, LL.s-1);
	ii D(UR.f, LL.s-1);
	int res = read(B)- (read(A)+read(D)) + read(C);
	return res;	
}

int main()
{
	memset (tree, 0, sizeof(tree));
	cout<<sizeof(tree)<<"\n";
		
	update(4,4,1);		
	update(3,4,2);
	update(5,5,2);
	update(1,2,2);
	ii lower_left(2,2);ii upper_right(5,5);
	cout<<read(lower_left, upper_right)<<"\n";
		

	return 0;
}






