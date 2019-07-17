#include <algorithm>
#include <iostream>
#include <string.h>
#include <cstdlib>
#include <vector>
//Form a BST out of switches, so that leaves woukd be triggers and will lead to the root again. One of the leaves (one that
//we will meet the last) will be the origin. Then enumerate the leaves by order of traverse (just simulate the process).
//Forming full binary tree can be up to 2N switches, so we can create only N leaves and don't build the part of tree we 
//won't require. It's better to remove the left part than the right one, because the last leave we'll visit will always be
//the rightmost one, so to get all states 'X' we can traverse all tree and by not removing the right part of tree we can
//always make sure the rightmost leaf will always indicate the end of an algorithm.
#include <string>
#include <bitset>
#include <math.h>
#include <queue>
#include <stack>
#include <set>
#include <map>
 
typedef long long ll;
typedef long double ld;
 
const ll MOD = 1e9 + 7, INF = 1e18 + 1;
 
using namespace std;

int n, m, a[1000000], ptr, x[1000000], y[1000000];

void answer (vector <int> C, vector <int> X, vector <int> Y);

struct Node
{
	int x;
	bool on;

	Node *l, *r;

	Node () : x (0), on (false), l (NULL), r (NULL) {}
};

Node *root, *origin;

Node* dfs_init (int n, int tl, int tr, bool rt)
{
	if (tr <= n) return root;

	Node* a = new Node ();

	if (rt) root = a;

	if (tl != tr)
	{
		a -> x = -(++ptr);
		a -> l = dfs_init (n, tl, (tl + tr) / 2, false);
		a -> r = dfs_init (n, (tl + tr) / 2 + 1, tr, false);
	}

	return a;
}

bool place_next (Node* t, int x)
{
	t -> on = !(t -> on);

	Node* to = new Node ();

	if (t -> on) to = t -> l;
	else to = t -> r;

	if (to == root) return false;
	else if (!to -> l) to -> x = x;
	else return place_next (to, x);

	return true;
}

void dfs_output (Node* t)
{
	if (!t -> l) return;

	x[-(t -> x) - 1] = t -> l -> x;
	y[-(t -> x) - 1] = t -> r -> x;

	if (t -> l != root) dfs_output (t -> l);
	if (t -> r != root) dfs_output (t -> r);
}

void create_circuit (int m, vector <int> A)
{
	origin = new Node ();

	int n = (int) A.size ();
	int n_ = n + 1;

	int start = 1, s = 0;

	while (start < n_) start <<= 1;

	dfs_init (start - n_, 1, start, true);

	int p = 0;

	while (p < n)
	{
		s++;
		if (place_next (root, A[p])) p++;
	}

	while (!place_next (root, 0));

	dfs_output (root);

	vector <int> C;

	C.push_back (-1);

	for (int i = 0; i < m; i++)
		C.push_back (-1);

	vector <int> X, Y;

	for (int i = 0; i < ptr; i++)
	{
		X.push_back (x[i]);
		Y.push_back (y[i]);
	}

	answer (C, X, Y);
}
