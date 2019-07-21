#include <algorithm>
#include <iostream>
#include <string.h>
#include <cstdlib>
//https://ioinformatics.org/files/ioi2016solutions.pdf#include <vector>
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
 
int p[1000000], sz[1000000];
 
set <int> mp;
 
struct stop
{
	int x;
	bool op;
 
	bool operator < (const stop& b)
	{
		if (x == b.x) return op > b.op;
		else return x < b.x;
	}
};
 
struct edge
{
	int u, v;
	ll c;
 
	bool operator < (const edge& b)
	{
		return c < b.c;
	}
};
 
vector <stop> v;
 
int find (int x)
{
	if (p[x] == x) return x;
	else return p[x] = find (p[x]);
}
 
void unite (int a, int b)
{
	a = find (a);
	b = find (b);
 
	if (a == b) return;
 
	if (sz[a] < sz[b]) swap (a, b);
 
	p[b] = a;
 
	sz[a] += sz[b];
}
 
int ind (int a, vector <int>& s)
{
	return lower_bound (s.begin(), s.end(), a) - s.begin ();
}
 
ll plan_roller_coaster (vector <int> s, vector <int> t)
{
	ll ans = 0, balance = 0;
 
	s.push_back (1e9);
	t.push_back (1);
 
	vector <int> coord;
 
	for (int i = 0; i < s.size (); i++)
	{
		v.push_back ({s[i], true});
		v.push_back ({t[i], false});
 
		mp.insert (s[i]);
		mp.insert (t[i]);
	}
 
	for (auto a : mp)
		coord.push_back (a);
 
	for (int i = 0; i < coord.size (); i++)
	{
		sz[i] = 1;
		p[i] = i;
	}
 
	for (int i = 0; i < s.size (); i++)
		unite (ind (s[i], coord), ind (t[i], coord));
 
	sort (v.begin(), v.end());
 
	vector <edge> tr;
 
	for (int i = 0; i < v.size (); i++)
	{
		if (v[i].op) balance++;
		else balance--;
 
		if (i != v.size () - 1) 
		{
			ans += max (0LL, balance * 1LL * (v[i+1].x - v[i].x));
			if (balance != 0) unite (ind (v[i].x, coord), ind (v[i+1].x, coord));
			tr.push_back ({ind (v[i].x, coord), ind (v[i+1].x, coord), (v[i+1].x - v[i].x)});
		}
	}
 
	sort (tr.begin(), tr.end());
 
	for (edge e : tr)
	{
		if (find (e.u) != find (e.v))
		{
			ans += e.c;
			unite (e.u, e.v);
		}
	}
 
	return ans;
}
