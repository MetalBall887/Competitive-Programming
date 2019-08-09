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
 
int mx_one, mn_one = 1e9;
 
int length (int l, int r, int d)
{
	return r - l + min (abs (r) + abs (l - d), abs (l) + abs (r - d));
}
 
int n;
 
string s, t;
 
int check (int x)
{
	vector < pair <int, int> > side (n), s_comp;
	string con;
 
	for (int i = 0; i < n; i++)
		if (s[i] == t[(i + n + x) % n]) con += '0';
		else con += '1';
 
	int to = mx_one - n;
	for (int i = 0; i < n; i++)
	{
		if (t[i] == '1') to = i;
 
		side[i].first = i - to;
	}
 
	to = mn_one + n;
	for (int i = n - 1; i >= 0; i--)
	{
		if (t[i] == '1') to = i;
 
		side[i].second = to - i;
	}
 
	for (int i = 0; i < n; i++)
		if (con[i] == '1') s_comp.push_back (side[i]);
 
	if (s_comp.empty ()) return abs (x);
	sort (s_comp.begin(), s_comp.end());
 
	int r = 0;
	int ans = s_comp.back ().first + abs (x + s_comp.back ().first);
 
	for (int i = s_comp.size () - 1; i > 0; i--)
	{
		r = max (r, s_comp[i].second);
		ans = min (ans, length (-s_comp[i-1].first, r, x));
	}
 
	r = max (r, s_comp[0].second);
	ans = min (ans, abs (r) + abs (x - r));
 
	return ans + s_comp.size ();
}
 
int main ()
{
	int ans = 1e9;
 
	cin >> s >> t;
 
	n = s.length ();
 
	for (int i = 0; i < n; i++)
		if (t[i] == '1')
		{
			mx_one = i;
			mn_one = min (mn_one, i);
		}
 
	if (mn_one == 1e9)
	{
		for (int i = 0; i < n; i++)
			if (s[i] == '1')
			{
				cout << -1;
				return 0;
			}
		cout << 0;
		return 0;
	}
 
	for (int i = 0; i < n; i++)
		ans = min (ans, min (check (i), check (i - n)));
 
	cout << ans;
 
}
