
#include<iostream>
#include<algorithm>
#include<string.h>
#include<math.h> 
#include <vector>
#define INVALID 99999
using namespace std;

struct Node
{
	int val;
	int lazy;
	Node()
	{
		val=INVALID;
		lazy=INVALID;
	}
	void merge(Node& l, Node& r)
	{
		val = min(l.val, r.val);
	}
	int mergeVal(int& val1, int& val2)
	{
		return min(val1, val2);
	}
	void updateVal(int value)
	{
		val = min(val, value);
	}
	void propagateLazy(int value)
	{
		lazy = min(lazy, value);
	}
	void resetLazy()
	{
		lazy = INVALID;
	}
	void resetNode()
	{
		val = INVALID;
		lazy = INVALID;
	}
};

Node* tree;
int N;

// build_tree(<TREE NODE>, <TREE NODE'S LEFTMOST INDEX>, <TREE NODE'S RIGHTMOST INDEX>, <INIT ARRAY>)
void build_tree(int node, int leftMost, int rightMost, vector<int>& init) 
{
	//cout<<leftMost<<" "<<rightMost<<" = "<<node<<"\n";
	if(leftMost > rightMost) return; // Out of range

	if(leftMost == rightMost) 
	{ // Leaf node
		tree[node].val = init[leftMost]; // Init value
		return;
	}

	build_tree(node*2, leftMost, (leftMost+rightMost)/2, init); // Init left child
	build_tree(node*2+1, 1+(leftMost+rightMost)/2, rightMost, init); // Init right child

	tree[node].merge(tree[node*2], tree[node*2+1]); 
}

void print_tree() 
{
	int n=pow(2, (ceil(log2(N)))+1);
	for(int i=1; i< n; i++)
	{
		cout<<"("<<i<<") "<<tree[i].val<<", "<<tree[i].lazy<<"\n";
	}
}


/**
 * Increment elements within range [end1, end2] with value value
 */
// update_tree(<TREE NODE>, <TREE NODE'S LEFTMOST INDEX>, <TREE NODE'S RIGHTMOST INDEX>, <UPDATE RANGE END1>, <UPDATE RANGE END2>, VALUE)
void update_tree(int node, int leftMost, int rightMost, int end1, int end2, int value) 
{
	//cout<<node<<" Leftmost: "<<leftMost<<" Rightmost: "<<rightMost<<" End1: "<<end1<<" End2: "<<end2<<" "<<value<<"\n";
	// Current segment is not within range [i, j]

	if(tree[node].lazy != INVALID) 
	{ 
		tree[node].updateVal(tree[node].lazy); // Update it
		if(leftMost != rightMost)
		{
			tree[node*2].propagateLazy(tree[node].lazy); // Mark child as lazy
			tree[node*2+1].propagateLazy(tree[node].lazy); // Mark child as lazy
		}
		tree[node].resetLazy(); // Reset it
	}
	if(leftMost > rightMost || leftMost > end2 || rightMost < end1) 
		return;

	// Segment is fully within range
	if(leftMost >= end1 && rightMost <= end2)
	{ 
		tree[node].updateVal(value);
		if(leftMost != rightMost) 
		{ 
			tree[node*2].propagateLazy(value); // Mark child as lazy
			tree[node*2+1].propagateLazy(value); // Mark child as lazy
		}
		return;
	}

	update_tree(node*2, leftMost, (leftMost+rightMost)/2, end1, end2, value); // Updating left child
	update_tree(1+node*2, 1+(leftMost+rightMost)/2, rightMost, end1, end2, value); // Updating right child

	tree[node].merge(tree[node*2], tree[node*2+1]); 
}

/**
 * Query tree to get min element value within range [end1, end2]
 */
// query_tree(<TREE NODE>, <TREE NODE'S LEFTMOST INDEX>, <TREE NODE'S RIGHTMOST INDEX>, <QUERY RANGE END1>, <QUERY RANGE END2>)
int query_tree(int node, int leftMost, int rightMost, int end1, int end2) 
{
	if(leftMost > rightMost || leftMost > end2 || rightMost < end1) return INVALID; // Out of range

	if(tree[node].lazy != INVALID) 
	{ // This node needs to be updated
		tree[node].updateVal(tree[node].lazy); // Update it
		if(leftMost != rightMost) 
		{
			tree[node*2].propagateLazy(tree[node].lazy); // Mark child as lazy
			tree[node*2+1].propagateLazy(tree[node].lazy); // Mark child as lazy
		}
		tree[node].resetLazy(); // Reset it
	}

	if(leftMost >= end1 && rightMost <= end2) // Current segment is totally within range [i, j]
		return tree[node].val;

	int q1 = query_tree(node*2, leftMost, (leftMost+rightMost)/2, end1, end2); // Query left child
	int q2 = query_tree(1+node*2, 1+(leftMost+rightMost)/2, rightMost, end1, end2); // Query right child

	return tree[node].mergeVal(q1,q2);
}

void reset_tree(int node, int leftMost, int rightMost) 
{
	if(leftMost > rightMost) return; // Out of range

	tree[node].resetNode();
	if(leftMost==rightMost)
		return;

	reset_tree(node*2,leftMost, (leftMost+rightMost)/2);	
	reset_tree(node*2+1,1+(leftMost+rightMost)/2, rightMost);	
}

// init(<INPUT VECTOR>)
void init(vector<int>& arr)
{
	N = arr.size();
	int tree_size = pow(2, (ceil(log2(N)))+1);
	tree = new Node[tree_size];
	build_tree(1, 0, N-1, arr);
}

int main() 
{

	int arr[] = {1,2,3,4,5,6};
	vector<int> vt(arr, arr+ sizeof(arr)/sizeof(int));
	
	init(vt);
	cout << query_tree(1, 0, N-1, 1, 3) << endl; // Get max element in range [1, 3]
	//print_tree();
	update_tree(1, 0, N-1, 0, 2, 5); // Increment range [0, 6] by 5. here 0, N-1 represent the current range.
	cout << query_tree(1, 0, N-1, 1, 3) << endl; // Get max element in range [1, 3]
}

