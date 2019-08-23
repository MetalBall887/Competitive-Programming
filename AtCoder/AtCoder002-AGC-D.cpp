#include <iostream>
#include <vector>
#include <stdio.h>
//let's pretend we have 1 query. Then it would be convenient to check if the maximal edge is <= x and then do a binary search
//for this, we can add all edges we have <= x to the DSU and find the sizes of components they are in. If it's >= z, then
//it's true. For each query then we can' t build DSU logN times but we can save all versions of DSU by persistent array
//notice, that path compression optimisation works, since we change only last version, which will speed our code up even more
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <queue>

using namespace std;

typedef long long ll;

const ll INF = 1e9;

struct Node
{
    int x, sz, p;
    Node *l, *r;
	
    Node (int x, int p, int sz, Node* l, Node* r) : x (x), sz (sz), p (p), l (l), r (r) {}
};

int n, m, q;

struct PersistentArray
{
    int size, start;
    
    vector <Node*> rt;
    
    Node* build (int l, int r)
    {
	if (l == r)
	{
	    return new Node (l, l, 1, NULL, NULL);
	}
	
	int m = (l + r) / 2;
	
	return new Node (0, 0, 0, build (l, m), build (m + 1, r));
    }
    
    void build (int n)
    {
	start = 1;
	
	while (start < n) start <<= 1;
	
	rt.push_back (build (0, start - 1));
    }
    
    Node* update (Node* x, int l, int r, int ind, int p, int sz)
    {
	if (l == r) return new Node (l, p, sz, NULL, NULL);
	
	int m = (l + r) / 2;
	
	if (ind <= m)
	{
	    return new Node (0, 0, 0, update (x -> l, l, m, ind, p, sz), x -> r);
	}
	else return new Node (0, 0, 0, x -> l, update (x -> r, m + 1, r, ind, p, sz));
    }
    
    Node* update (Node* rt, int x, int p, int sz)
    {
	return update (rt, 0, start - 1, x, p, sz);
    }
    
    Node get (Node* x, int l, int r, int ind)
    {
	if (l == r) return *x;
	
	int m = (l + r) / 2;
	
	if (ind <= m) return get (x -> l, l, m, ind);
	else return get (x -> r, m + 1, r, ind);
    }
    
    Node get (int version, int x)
    {
	return get (rt[version], 0, start - 1, x);
    }
    
    void print (int v)
    {
	for (int i = 0; i < n; i++)
	{
	    cout << get (v, i).p << ' ';
	}
	cout << endl;
    }
} dsu;

Node find (int v, Node x)
{
    if (x.x == x.p) return x;
    Node p = dsu.get (v, x.p);
    return find (v, p);
}

void update (int v, int i, int j)
{
    Node a = find (v, dsu.get (v, i));
    Node b = find (v, dsu.get (v, j));
    
    if (a.x == b.x) 
    {
	dsu.rt.push_back (dsu.rt.back ());
	return;
    }
    
    if (a.sz < b.sz) swap (a, b);
    
    
    auto temp = dsu.update (dsu.rt.back (), a.x, a.p, a.sz + b.sz);
    dsu.rt.push_back (dsu.update (temp, b.x, a.x, b.sz));
}

int main ()
{
    cin >> n >> m;
    
    dsu.build (n);
    
    //dsu.print (0);
    
    for (int i = 0; i < m; i++)
    {
	int u, v;
	
	scanf ("%d%d", &u, &v);
	
	u--;
	v--;
	
	update (i, u, v);
	
	//dsu.print (i + 1);
    }
    
    cin >> q;
    
    for (int i = 0; i < q; i++)
    {
	int l = 0, r = m, x, y, z;
	
	scanf ("%d%d%d", &x, &y, &z);
	x--;
	y--;
	
	while (l < r)
	{
	    int mid = (l + r) / 2;
	    
	    auto a = find (mid, dsu.get (mid, x));
	    auto b = find (mid, dsu.get (mid, y));
	    
	    if (a.x == b.x)
	    {
		if (a.sz < z) l = mid + 1;
		else r = mid;
	    }
	    else
	    {
		if (a.sz + b.sz < z) l = mid + 1;
		else r = mid;
	    }
	}
	
	printf ("%d\n", l);
    }
}
