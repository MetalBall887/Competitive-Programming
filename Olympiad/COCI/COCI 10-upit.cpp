#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <cstdlib>
//implemented a treap with range updates
#include <vector>
#include <string>
#include <random>
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

int n, q;

struct Node
{
	int x, y, sz, count, q_sum, reset, sum, node_sum;
	Node * l, * r;

	Node (int x, int y, int node_sum) : x (x), y (y), node_sum (node_sum)
	{
		q_sum = reset = count = 0;
		sz = 1;
		sum = node_sum;
		l = r = NULL;
	}
};

typedef Node* pNode;

struct Treap
{
	pNode root;

	int val (pNode x)
	{
		return (x ? x -> sz : 0);
	}

	void pull (pNode x)
	{
		if (!x) return;
		x -> sz = 1;
		x -> sum = x -> node_sum;

		if (x -> l)
		{
			push (x -> l);
			x -> sz += x -> l -> sz;
			x -> sum += x -> l -> sum;
		}

		if (x -> r)
		{
			push (x -> r);
			x -> sz += x -> r -> sz;
			x -> sum += x -> r -> sum;
		}
	}

	void reset (pNode x)
	{
		x -> count = 0;
		x -> q_sum = 0;
		x -> sum = 0;
		x -> node_sum = 0;
		x -> reset = 1;
	}

	void push (pNode x)
	{
		if (!x) return;

		x -> node_sum = (x -> reset ? 0 : x -> node_sum) + x -> q_sum;
		x -> sum = (x -> reset ? 0 : x -> sum) + (x -> q_sum) * (x -> sz);

		if (x -> count)
		{
			x -> node_sum += x -> count * (val (x -> l) + 1);
			x -> sum += (x -> count) * (x -> sz + 1) * (x -> sz) / 2;
		}

		if (x -> l)
		{
			if (x -> reset) reset (x -> l);
			x -> l -> q_sum += x -> q_sum;
			x -> l -> count += x -> count;
		}

		if (x -> r)
		{
			if (x -> reset) reset (x -> r);
			x -> r -> q_sum += x -> q_sum + (x -> count) * (val (x -> l) + 1);
			x -> r -> count += x -> count;
		}

		x -> count = x -> q_sum = x -> reset = 0;
	}

	void split (pNode x, int key, pNode& l, pNode& r, int ind = 1)
	{
		push (x);

		if (!x) l = r = NULL;
		else 
		{
			ind += val (x -> l);
			if (key <= ind)
			{
				split (x -> l, key, l, x -> l, ind - val (x -> l));
				r = x;
			}
			else
			{
				split (x -> r, key, x -> r, r, ind + 1);
				l = x;
			}

			pull (x);
		}
	}

	void merge (pNode& x, pNode l, pNode r)
	{
		push (l);
		push (r);

		if (!l) x = r;
		else if (!r) x = l;
		else if (l -> y > r -> y)
		{
			merge (l -> r, l -> r, r);
			x = l;
		}
		else
		{
			merge (r -> l, l, r -> l);
			x = r;
		}

		pull (x);
	}

	void insert (int x, int y, int cost)
	{
		pNode l, r, m = new Node (x, y, cost);

		split (root, x, l, r);

		merge (l, l, m);
		merge (root, l, r);
	}

	void update (int type, int qx, int ql, int qr)
	{
		pNode l, m, r;

		if (type == 1)
		{
			split (root, ql, l, r);
			split (r, qr + 1, m, r);

			reset (m);
			m -> q_sum = qx;
			push (m);

			merge (l, l, m);
			merge (root, l, r);
		}
		else
		{
			split (root, ql, l, r);
			split (r, qr + 1, m, r);

			m -> count += qx;
			push (m);

			merge (l, l, m);
			merge (root, l, r);
		}
	}

	int get (int ql, int qr)
	{
		pNode l, m, r;

		split (root, ql, l, r);
		split (r, qr - ql + 2, m, r);

		push (m);

		int s = m -> sum;

		merge (l, l, m);
		merge (root, l, r);

		return s;
	}
} tr;

int main ()
{
	cin >> n >> q;

	random_device dev;
	mt19937 rng(dev ());
	uniform_int_distribution<mt19937::result_type> dist (1, 1e9);

	for (int i = 0; i < n; i++)
	{
		int a;

		scanf ("%d", &a);

		tr.insert (i + 1, dist (rng), a);
	}

	for (int i = 0; i < q; i++)
	{
		int type, x, l, r;
		scanf ("%d", &type);

		if (type < 3)
		{
			scanf ("%d%d%d", &l, &r, &x);

			tr.update (type, x, l, r);
		}
		else if (type == 3)
		{
			scanf ("%d%d", &l, &x);
			tr.insert (l, dist (rng), x);
		}
		else
		{
			scanf ("%d%d", &l, &r);
			printf ("%d\n", tr.get (l, r));
		}
	}
}
