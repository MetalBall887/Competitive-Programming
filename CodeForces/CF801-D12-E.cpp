#include <iostream>
#include <cstdlib>
#include <string>
#include <set>
#include <map>
#include <algorithm>
//sort all possible prefix products by their gcd with m then find the longest subsequence
//with dynamic programming. After that construct the original sequence with linear equations.
#include <bitset>
#include <queue>
#include <math.h>
#include <stack>
#include <vector>
#include <string.h>

typedef long long ll;
 
const ll MOD = 1e9 + 7, INF = 1e18 + 1;
 
using namespace std;

ll n, m, banned[200000], p[200000], len[200000], p_m;
ll last[200000];

vector <ll> fact[200010];

ll gcd (ll a, ll b)
{
	if (!b) return a;
	return gcd (b, a % b);
}

ll phi (ll n) 
{
	ll result = n;
	
	for (ll i = 2; i * i <= n; i++)
		if (n % i == 0) 
		{
			while (n % i == 0) n /= i;
			result -= result / i;
		}
	if (n > 1) result -= result / n;

	return result;
}

ll qpow (ll a, ll b, ll m)
{
	ll s = 1;
	while (b)
	{
		if (b & 1) s = s * a % m;
		b /= 2;
		a = a * a % m;
	}

	return s;
}

ll solve (ll a, ll b)
{
	int a_d = a, b_d = b, m_d = m;

	int d = gcd (a_d, m);

	a_d /= d;
	m_d /= d;
	b_d /= d;

	return b_d * qpow (a_d, phi (m_d) - 1, m_d) % m_d;
}

int main ()
{
	cin >> n >> m;

	p_m = phi (m) - 1;

	for (ll i = 0; i < n; i++)
	{
		ll x;

		scanf ("%lld", &x);

		banned[x] = 1;
	}

	if (m == 1)
	{
		if (!banned[0]) cout << "1\n0";
		else cout << 0;
		return 0;
	}

	for (ll i = 1; i <= m; i++)
	{
		for (ll j = i; j <= m; j += i)
			fact[j].push_back (i);
	}


	vector < pair <ll, ll> > v;

	for (ll i = 1; i < m; i++)
		v.emplace_back (make_pair (gcd (i, m), i));

	sort (v.begin(), v.end());

	for (ll i = 0; i < m; i++)
	{
		len[i] = 1;
		p[i] = 1;
		last[i] = -1;
	}
	
	last[1] = 0;

	ll mx_ind = -1;

	for (int i = 1; i < v.size (); i++)
	{
		if (banned[v[i].second]) continue;
        
		for (ll f : fact[v[i].second])
			if (last[f] != -1 && len[v[i].second] < len[v[last[f]].second] + 1)
			{
				len[v[i].second] = len[v[last[f]].second] + 1;
				p[v[i].second] = v[last[f]].second;
			}

		last[v[i].first] = i;

		if (mx_ind == -1 || len[mx_ind] < len[v[i].second])
			mx_ind = v[i].second;
	}

	ll x = mx_ind;

	vector <ll> ans;

	if (mx_ind == -1)
	{
		if (!banned[0]) ans.push_back (0);

		cout << ans.size () << endl;

		for (ll a : ans)
			printf ("%lld ", a);

		return 0;
	}

	while (x != 1)
	{
		ll a = p[x], b = x;

		ans.push_back (solve (a, b));

		if (a * solve (a, b) % m != b) cout << "NO!";

		x = p[x];
	}

	if (!banned[1]) ans.push_back (1);

	reverse (ans.begin(), ans.end());
	if (!banned[0]) ans.push_back (0);

	cout << ans.size () << endl;

	ll k = 1;

	for (ll a : ans)
	{
		printf ("%lld ", a);
	}
}
