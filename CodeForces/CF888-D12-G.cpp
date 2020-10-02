#include <iostream>
#include <cstdlib>
#include <string>
#include <set>
#include <map>
#include <algorithm>
#include <bitset>
#include <queue>
#include <math.h>
#include <stack>
#include <vector>
#include <string.h>
#include <random>
//We're using Boruvka algorithm with keeping all weights of nodes out of a current component in a trie. Each phase can be O(n) so we can first keep all the weights
//in the trie and for each component delete all weights in the component, find the closest for each vertex inside of the component and put all deleted weights back
//For all components summarized it's O(n), each operation with a trie is logW, so the complexity is O(nlognlogW)
 
typedef long long ll;
 
const ll MOD = 1e9 + 7, INF = 1e18;
 
using namespace std;
 
ll n, f[200000];
 
set < pair <int, int> > ans;
 
ll p[200000], sz[200000];
 
vector <ll> d[200000];
 
pair <ll, ll> min_edge[200000];
 
ll numbers[7000000];
 
ll find (ll x)
{
	if (p[x] == x) return x;
	else return p[x] = find (p[x]);
}
 
void unite (ll a, ll b)
{
	a = find (a);
	b = find (b);
 
	if (a == b) return;
 
	if (sz[a] < sz[b]) 
	{
		unite (b, a);
		return;
	}
 
	p[b] = a;
	sz[a] += sz[b];
}
 
struct node
{
	int num;
	int next[2];
};
 
vector <node> a;
 
ll ptr = 0;
 
void add (ll ind)
{
	ll cur = 0, x = f[ind];
 
	for (ll i = 29; i >= 0; i--)
	{
		ll s;
		if (x & (1LL << i)) s = 1;
		else s = 0;
 
		if (a[cur].next[s] == 0)
		{
			a.push_back ({0, 0, 0});
			a[cur].next[s] = ++ptr;
		}
 
		cur = a[cur].next[s];
 
		a[cur].num++;
	}
 
	numbers[cur] = ind;
}
 
void remove (ll ind)
{
 
	ll cur = 0, x = f[ind];
 
	for (ll i = 29; i >= 0; i--)
	{
		ll s;
		if (x & (1LL << i)) s = 1;
		else s = 0;
 
		cur = a[cur].next[s];
 
		a[cur].num--;
	}
}
 
pair <ll, ll> find_xor (ll ind)
{
	ll cur = 0, ans = 0, x = f[ind];
 
	for (ll i = 29; i >= 0; i--)
	{
		ll s;
 
		if (x & (1LL << i)) s = 1;
		else s = 0;
 
		if (!a[cur].next[s] || a[a[cur].next[s]].num == 0)
		{
			cur = a[cur].next[1 - s];
			ans = ans * 2 + 1 - s;
		}
		else 
		{
			cur = a[cur].next[s];
			ans = ans * 2 + s;
		}
	}
 
	return make_pair (ans ^ f[ind], numbers[cur]);
}
 
int main ()
{
	cin >> n;
 
	a.push_back ({0, 0, 0});
 
	set <ll> dist;
 
	for (ll i = 0; i < n; i++)
	{
		scanf ("%lld", &f[i]);
 
		dist.insert (f[i]);
	}
 
	n = 0;
 
	for (auto it : dist)
	{
		f[n] = it;
		add (n);
		n++;
	}
 
	for (ll i = 0; i < n; i++)
	{
		p[i] = i;
		sz[i] = 1;
	}
 
	ll sum = 0;
 
	while (sz[find (0)] != n)
	{
		ans.clear ();
		for (ll i = 0; i < n; i++)
			d[i].clear ();
 
 
		for (ll i = 0; i < n; i++)
		{
			d[find (i)].push_back (i);
			min_edge[find (i)] = {INF, INF};
		}
 
		for (ll i = 0; i < n; i++)
		{
			ll l = 0;
			if (d[i].empty ()) continue;
 
			for (ll x : d[i])
				remove (x);
 
			for (ll x : d[i])
			{
				auto g = find_xor (x);
				if (min_edge[i] > g)
				{
					min_edge[i] = g;
					l = x;
				}
			}
 
			for (ll x : d[i])
				add (x);
 
			ans.insert ({min (l, min_edge[i].second), max (l, min_edge[i].second)});
		}
 
		for (auto it : ans)
		{
			sum += f[it.first] ^ f[it.second];
			unite (it.first, it.second);
		}
	}
 
	cout << sum;
}
