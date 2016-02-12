#include <iostream>
#include <string.h>
#include <algorithm>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <climits>
using namespace std;

int init(vector<int>& vt, vector<int>& min_tree, int low, int high, int index)
{
	if(low>high)
		return INT_MAX;
	int mid = low + (high-low)/2;
	if(low==high)
		min_tree[index] = vt[low];
	else
	{
		min_tree[index] = min(init(vt, min_tree, low, mid, 2*index),init(vt, min_tree, mid+1, high, 2*index+1));	
	}
	return min_tree[index];
}

int query(vector<int>& min_tree, int ql, int qh, int tl, int th, int index)
{
	if(ql<= tl && qh>=th)
		return min_tree[index];
	if(qh< tl || ql>th)
		return INT_MAX;
	int mid = tl + (th-tl)/2;
	return min(query(min_tree, ql, qh, tl, mid, 2*index), query(min_tree, ql, qh, mid+1, th, 2*index+1));
}

int update(vector<int>& min_tree, int low, int high, int index,int val, int ind)
{
		if(low==high && low==index)
				min_tree[ind] =  val;
		else if(index>=low && index<=high)
		{
			int mid = low + (high-low)/2;
			min_tree[ind] =  min(update(min_tree, low, mid, index, val, 2*ind), update(min_tree, mid+1, high, index, val, 2*ind+1));
		}
		return min_tree[ind];
}

void print(vector<int>& min_tree, int low, int high, int index)
{
	cout<<low<<" "<<high<<" "<<min_tree[index]<<"\n";
	if(low==high)
		return;
	int  mid = low + (high-low)/2;
	print(min_tree, low, mid, 2*index);
	print(min_tree, mid+1, high, 2*index+1);
}

int main()
{
	vector<int> vt{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	vector<int> min_tree(2*vt.size()+1,INT_MAX);
	init(vt, min_tree, 0, vt.size()-1,1);
	cout<<query(min_tree, 4,13, 0, vt.size()-1, 1)<<"\n";
	update(min_tree, 0 ,vt.size()-1, 4, -1, 1);
	cout<<query(min_tree, 4,13, 0, vt.size()-1, 1)<<"\n";
	//print(min_tree, 0, vt.size()-1, 1);
	return 0;
}
