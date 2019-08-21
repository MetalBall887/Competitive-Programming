#include <iostream>
#include <vector>
//let's think about a vertex with the biggest distance sum. It's supposed to ba the leaf, and we can determine its parent
//uniquely (because all sums are distinct). By knowing its subtree size we can define dist sums of parent. That means, for
//each vertex we can determine its of children, for each child its children too and so on -> we can determine subtree and
//subtree size. Depending on the subtree size we can then find the dist sum of its parent and so on to define the tree itself.
//In the end, check the tree for correctness.
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cmath>
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e9;
 
vector < pair <ll, ll> > v;
 
ll n, sz[1000000], r[1000000], sum;
 
bool ans = true;
 
vector <ll> g[1000000];
 
ll dfs (ll x, ll p)
{
	ll sum = sz[x] - 1;
 
	for (ll to : g[x])
		if (to != p)
			sum += dfs (to, x);
 
	return sum;
}
 
int main () 
{
    cin >> n;
    
    for (ll i = 0; i < n; i++)
    {
		ll d;
		scanf ("%lld", &d);
		
		v.emplace_back (d, i);
 
		r[i] = d;
    }
    
    sort (v.begin (), v.end ());
    
    for (ll i = n - 1; i > 0; i--)
    {
		ll x = v[i].second, d = v[i].first;
		
		sz[x] = 1;
		
		for (ll to : g[x])
		    sz[x] += sz[to];
 
		sum += sz[x];
 
		ll k = lower_bound (v.begin (), v.end (), make_pair (d + 2 * sz[x] - n, -1LL)) - v.begin ();
		
		if (k >= i || v[k].first != d + 2 * sz[x] - n)
		{
		    cout << -1;
		    return 0;
		}
		
		g[v[k].second].push_back (x);
    }
 
    if (sum != v[0].first)
    {
		cout << -1;
		return 0;
    }
    
    for (ll i = 0; i < n; i++)
		for (ll to : g[i])
		{
		    printf ("%lld %lld\n", i + 1, to + 1);
		}
}
