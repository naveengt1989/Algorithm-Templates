
///////////////////////////////////// 

// File Name :

// Purpose :

// Creation Date : 20-10-2015

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
using namespace std;
#define CLOCK_START double start_t = clock();
#define CLOCK_STOP cout << "Took: " << ((clock() - start_t) / CLOCKS_PER_SEC);
#define FOR(i,a,b) for(int i=a; i<b; i++)
#define ii pair<int,int>
#define vi vector<int>
#define CLR(a, x) memset( a, x, sizeof( a ) )
#define LL long long
#define ULL unsigned long long
#define MAXALPHA 26

class TrieNode
{
	public:
	TrieNode* child[MAXALPHA];
	bool isEnd;
	TrieNode()
	{
		isEnd= false;
		for(int i=0; i< MAXALPHA; i++)
			child[i]=NULL;
	}
};

void insert(TrieNode* root, string& str)
{
	TrieNode* cur = root;
	for(int i=0; i< str.length(); i++)
	{
		if(cur->child[str[i]-'a']==NULL)
			cur->child[str[i]-'a']= new TrieNode();
		cur = cur->child[str[i]-'a'];	
	}
	cur->isEnd=true;
}

bool search(TrieNode* root, string& str)
{
	TrieNode* cur = root;
	for(int i=0; i< str.length(); i++)
	{
		if(cur->child[str[i]-'a']==NULL)
			return false;
		else
			cur = cur->child[str[i]-'a'];	
	}
	if(cur->isEnd)
		return true;
	else
		return false;
}

bool isValid(TrieNode* root, string& str)
{
	TrieNode* cur = root;
	for(int i=0; i< str.length(); i++)
	{
		if(cur->child[str[i]-'a']==NULL)
			return false;
		else
			cur = cur->child[str[i]-'a'];	
	}
	return true;
}

int main()
{
	TrieNode* root = new TrieNode();
	string str1= "naveen";	
	string str2= "jinde";	
	insert(root, str1);
	if(search(root, str1))
		cout<<str1<<" FOUND!!\n";
	else
		cout<<str1<<"NOT FOUND!!\n";
	if(search(root, str2))
		cout<<str2<<" FOUND!!\n";
	else
		cout<<str2<<"NOT FOUND!!\n";
	
	return 0;
}


