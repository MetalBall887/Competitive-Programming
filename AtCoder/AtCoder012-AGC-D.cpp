#include <algorithm>
#include <iostream>
#include <string.h>
#include <cstdlib>
#include <vector>
#include <string>
//Let balls be vertices, there is an edge between vertices if corresponding balls can change places directly. Then, if two vertices
//lie in one connected component, corresponding balls can change places indirectly, so balls inside one connected component can permutate
//freely. First let's solve a problem where  there is only one color. Then, if some ball can be paired with another one, they both can be paired
//with one with minimal weight, so we only have to check the connection between the lightest ball and any else. Notice that algorithm is 
//identical for colors pairwise distinct. Let A be a set of all balls with the color a. x(A) is the arbitrary ball from the set, 
//m(A) is the lightest one. Key observation is, if there is a path between some two balls, each ball in the path can be replaced with the
//lightest of the same color. Indeed, if x(A) and x(B) are those endpoints and x(A)<->x(B), we can build a path x(A)<->m(B)<->m(A)<->x(B)
//where <-> allows vertices m(X) in between. So to solve the original problem, we can leave only lightest balls of each color in
//a graph, group them in components (since their colors are pairwise different, we can apply an algorithm similar to above) and attach
//other vertices to any from this subset of minimums and then count combinations with a simple formula.
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
 
ll p[1000000], sz[1000000], sum[1000000], n, X, Y;
ll fact[1000000], ans = 1, min_c[1000000], u[1000000], inv[1000000];

map <ll, ll> mp[1000000];

struct Component
{
	ll mn, c;

} cm[1000000];

ll qpow (ll a, ll b)
{
	ll s = 1;

	while (b)
	{
		if (b & 1) s = (s * a) % MOD;
		a = a * a % MOD;
		b >>= 1;
	}

	return s;
}

vector < pair <ll, ll> > s;

struct ball
{
	ll c, w;

	bool operator < (const ball& b) const
	{
		return w < b.w;
	}

} a[1000000];

ll find (ll x)
{
	if (x == p[x]) return x;
	return p[x] = find (p[x]);
}

void unite (ll a, ll b)
{
	a = find (a);
	b = find (b);

	if (a == b) return;

	if (sz[a] < sz[b]) swap (a, b);

	p[b] = a;

	sz[a] += sz[b];
}
 
int main ()
{
	cin >> n >> X >> Y;

	fact[0] = inv[0] = 1;
	for (ll i = 1; i <= n; i++)
		fact[i] = (i * fact[i-1]) % MOD;

	inv[n] = qpow (fact[n], MOD - 2);

	for (ll i = n - 1; i >= 0; i--)
		inv[i] = (i + 1) * inv[i+1] % MOD;

	for (ll i = 0; i < n; i++)
	{
		p[i] = i;
		sz[i] = 1;
		ll c, w;

		scanf ("%lld%lld", &c, &w);

		a[i] = {c, w};
	}

	sort (a, a + n);

	for (int i = 0; i <= n; i++)
		min_c[i] = -1;

	for (ll i = 0; i < n; i++)
	{
		if (min_c[a[i].c] == -1) min_c[a[i].c] = i;
		else if (a[min_c[a[i].c]].w + a[i].w <= X) unite (min_c[a[i].c], i);
	}

	for (ll i = 1; i <= n; i++)
		if (min_c[i] != -1)
			s.push_back ({a[min_c[i]].w, min_c[i]});

	sort (s.begin (), s.end ());

	for (ll i = 0; i < n; i++)
	{
		if (a[s[0].second].c == a[i].c)
		{//had no brackets here so else belonged to the second if insead of the first one
			if (s.size () > 1 && s[1].first + a[i].w <= Y) unite (s[1].second, i);
		}
		else if (s[0].first + a[i].w <= Y)
		{
			unite (s[0].second, i);
		}
	}

	for (ll i = 1; i < s.size (); i++)
		if (s[i].first + s[0].first <= Y) unite (s[i].second, s[0].second);

	for (ll i = 0; i < n; i++)
		mp[find (i)][a[i].c]++;

	for (ll i = 0; i < n; i++)
		if (p[i] == i)
		{
			ll den = 1;
			for (auto a : mp[i])
				den = (den * inv[a.second]) % MOD;

			ans = (ans * (fact[sz[i]] * den % MOD)) % MOD;
		}

	cout << ans;

}
