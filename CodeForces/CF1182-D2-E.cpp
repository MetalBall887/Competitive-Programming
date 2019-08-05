#include <algorithm>
#include <iostream>
#include <string.h>
#include <cstdlib>
#include <vector>
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
 
struct Matrix
{
	ll t[5][5];
	Matrix (vector <string> s)
	{
		for (ll i = 0; i < 5; i++)
			for (ll j = 0; j < 5; j++)
				t[i][j] = s[i][j] - '0';
	}
 
	Matrix (ll x)
	{
		memset (t, 0, sizeof (t));
 
		for (ll i = 0; i < 5; i++)
			t[i][i] = x;
	}
 
	ll* operator[] (const ll& x)
	{
		return t[x];
	}
};
 
Matrix mult (Matrix a, Matrix b)
{
	Matrix s (0);
 
	for (ll i = 0; i < 5; i++)
		for (ll j = 0; j < 5; j++)
			for (ll k = 0; k < 5; k++)
				s[i][j] += (a[i][k] % (MOD - 1) * b[k][j] % (MOD - 1)) % (MOD - 1);
 
	return s;
}
 
Matrix qpow (Matrix a, ll b)
{
	Matrix s (1);
 
	while (b)
	{
		if (b & 1) s = mult (s, a);
		b >>= 1;
		a = mult (a, a);
	}
 
	return s;
}
 
ll qpow (ll a, ll b)
{
	ll s = 1;
 
	while (b)
	{
		if (b & 1) s = (s * a) % MOD;
		b >>= 1;
		a = (a * a) % MOD;
	}
 
	return s;
}
 
int main ()
{
	ll ans = 1;
 
	vector <string> s;
	s.push_back ("11000");
	s.push_back ("10100");
	s.push_back ("10000");
	s.push_back ("10010");
	s.push_back ("00021");
 
	Matrix b (s);
 
	ll f1, f2, f3, C, n;
 
	cin >> n >> f1 >> f2 >> f3 >> C;
 
	Matrix f (0);
 
	f[0][3] = 2;
	f[0][4] = 1;
 
	b = mult (f, qpow (b, (n - 3)));
 
	ans = qpow (C, b[0][0]) % MOD;
 
	s.clear ();
	s.push_back ("11000");
	s.push_back ("10100");
	s.push_back ("10000");
	s.push_back ("00000");
	s.push_back ("00000");
 
	Matrix a (s);
 
	Matrix k (0), c (0);
 
	k[0][2] = 1;
 
	c = mult (k, qpow (a, n - 3));
 
	ans = ans * qpow (f1, c[0][0] % (MOD - 1)) % MOD;
 
	k[0][2] = 0;
	k[0][1] = 1;
 
	c = mult (k, qpow (a, n - 3));
 
	ans = ans * qpow (f2, c[0][0] % (MOD - 1)) % MOD;
 
	k[0][1] = 0;
	k[0][0] = 1;
 
	c = mult (k, qpow (a, n - 3));
 
	ans = ans * qpow (f3, c[0][0] % (MOD - 1)) % MOD;
 
	cout << ans;
}
