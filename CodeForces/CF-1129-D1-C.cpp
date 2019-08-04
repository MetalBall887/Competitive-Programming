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
 
using namespace std;
 
typedef long long ll;
 
const ll MOD = 1e9 + 7, INF = 1e15;
 
ll n, m, d[200000];
 
bool check (string& s, int i)
{
	if (s[i] == '1' && s[i + 1] == '1' && s[i + 2] == '0' && s[i + 3] == '0') return false;
	if (s[i] == '1' && s[i + 1] == '0' && s[i + 2] == '1' && s[i + 3] == '0') return false;
	if (s[i] == '0' && s[i + 1] == '1' && s[i + 2] == '1' && s[i + 3] == '1') return false;
	if (s[i] == '1' && s[i + 1] == '1' && s[i + 2] == '1' && s[i + 3] == '1') return false;
 
	return true;
}
 
int z_function (string& s)
{
	int n = s.length ();
 
	vector <int> z (n);
 
	int l = 0, r = 0;
 
	int ans = 0;
 
	for (int i = 1; i < n; i++)
	{
		if (r >= i) z[i] = min (z[i - l], r - i + 1);
 
		while (i + z[i] < n && s[i + z[i]] == s[z[i]]) z[i]++;
 
		if (r < i + z[i] - 1)
		{
			l = i;
			r = i + z[i] - 1;
		}
 
		ans = max (ans, z[i]);
	}
 
	return ans;
}
 
int main () 
{
	string s;
 
	cin >> m;
 
	ll ans = 0;
 
	for (int i = 0; i < m; i++)
	{
		string k;
 
		cin >> k;
 
		s = k[0] + s;
 
		int mix = z_function (s);
 
		for (int j = 0; j < s.length (); j++)
			d[j] = 0;
 
		d[0] = 1;
		if (i >= 1) d[1] = 1;
		if (i >= 2) d[2] = 1;
		if (i >= 3 && check (s, 0)) d[3] = 1;
 
		if (!mix) ans += d[0];
 
		for (int j = 1; j < s.length (); j++)
		{
 
			if (j >= 1) d[j] = (d[j-1] + d[j]) % MOD;
			if (j >= 2) d[j] = (d[j-2] + d[j]) % MOD;
			if (j >= 3) d[j] = (d[j-3] + d[j]) % MOD;
			if (j >= 4 && check (s, j - 3)) d[j] = (d[j-4] + d[j]) % MOD;
 
			if (j >= mix) ans = (ans + d[j]) % MOD;
		}
 
		printf ("%lld\n", ans);
	}
 
 
}
