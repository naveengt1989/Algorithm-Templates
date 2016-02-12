
///////////////////////////////////// 

// File Name :

// Purpose :

// Creation Date : 24-01-2015

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
using namespace std;
#define getcx getchar_unlocked
#define ULL unsigned long long
void initialize(vector<int>& A, int node, int start, int end, int segT[])
{
	if(start==end) // leaf node
	{
		segT[node]= start;
		return;
	}

	initialize(A, 2*node+1, start, start + (end-start)/2, segT);
	initialize(A, 2*node+2, start + (end-start)/2 +1, end, segT);
	if(A[segT[2*node+1]] > A[segT[2*node+2]])
		segT[node] = segT[2*node+2];
	else
		segT[node] = segT[2*node+1];


}


int query (vector<int>& A, int node, int start, int end, int qstart, int qend, int segT[])
{
	if(qstart>end || qend < start)// no intersection
		return -1;

	if(start>=qstart && end <= qend)// full overlap
		return A[segT[node]];

	int leftRes = query(A,2*node+1, start, start + (end-start)/2, qstart, qend, segT);
	int rightRes = query(A,2*node+2, start + (end-start)/2+1,end, qstart, qend, segT);
	
	//cout<<leftRes<<" "<<start<<" "<<start + (end-start)/2<<" "<<rightRes<<" "<<start + (end-start)/2+1<<" "<<end<<"\n";

	if(leftRes != -1 && rightRes != -1)
		return min(leftRes, rightRes);
	else if (leftRes == -1)
		return rightRes;
	else if(rightRes == -1)
		return leftRes;
	else
		cout<<"Unexpected\n";
}


struct Tree
{
	int V;
	vector<int>* adj;
	Tree(int ver)
	{
		V=ver;
		adj = new vector<int>[V+1];
	}
};

void constructTree(Tree& tr)
{
	tr.adj[1].push_back(2);
	tr.adj[1].push_back(3);
	tr.adj[1].push_back(4);
	tr.adj[3].push_back(5);
	tr.adj[3].push_back(6);
	tr.adj[3].push_back(7);
	tr.adj[6].push_back(8);
	tr.adj[6].push_back(9);
	tr.adj[7].push_back(10);
	tr.adj[7].push_back(11);
	tr.adj[10].push_back(12);
	tr.adj[10].push_back(13);
}

void dfs(int root, vector<int>& arr, int* firstIndex,Tree& tr)
{
	arr.push_back(root);
	firstIndex[root] = arr.size();
	for(int i=0; i< tr.adj[root].size(); i++)
	{
		dfs(tr.adj[root][i], arr, firstIndex, tr);
		arr.push_back(root);
	}
}

int main()
{
	/*int A[]={1,2,3,4,5,6,7,8,9,10};	
	int N = sizeof(A)/sizeof(int);
	
	int *segT = new int[2*N-1];
	

	initialize(A,0, 0, N-1, segT);

	cout<<query(A,0, 0, N-1, 3, N-1, segT)<<"\n";*/


	// tree construction
	int NUM_VERTICES=13;
	Tree tr(NUM_VERTICES);	
	constructTree(tr);	
	vector<int> lcaToRmqArray;
	int* nodeFirstOccurence = new int[NUM_VERTICES+1];
	dfs(1, lcaToRmqArray, nodeFirstOccurence, tr);
	

	int u_node=9;
	int v_node=12;
	int N=lcaToRmqArray.size();
	int *segT = new int[2*N-1];
	initialize(lcaToRmqArray,0, 0, N-1, segT);
	cout<<query(lcaToRmqArray,0, 0, N-1, min(nodeFirstOccurence[u_node], nodeFirstOccurence[v_node]), max(nodeFirstOccurence[u_node], nodeFirstOccurence[v_node]), segT)<<"\n";
	
	return 0;
}


