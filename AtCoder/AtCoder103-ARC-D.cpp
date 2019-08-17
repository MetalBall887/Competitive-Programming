#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <string.h>
//https://img.atcoder.jp/arc103/editorial.pdf
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
ll n, k, even, x[1000000], y[1000000];
 
bool is_in (ll c_x, ll c_y, ll x, ll y, ll r)
{
	return (abs (c_x + c_y - (x + y)) <= r && abs (c_x - c_y - (x - y)) <= r);
}
 
string find (ll x, ll y)
{
	string s;
 
	ll c_x = 0, c_y = 0;
 
	if (even) 
	{
		s += 'U';
		c_y++;
	}
 
	ll sum = 0;
 
	for (ll i = 34; i >= 0; i--)
		sum += (1LL << i);
 
	for (ll i = 34; i >= 0; i--)
	{
		//cout << x << ' ' << y << ' ' << c_x << ' ' << c_y << endl;
 
		sum -= (1LL << i);
 
		if (is_in (c_x, c_y + (1LL << i), x, y, sum))
		{
			s += 'U';
			c_y += (1LL << i);
		}
		else if (is_in (c_x + (1LL << i), c_y, x, y, sum))
		{
			s += 'R';
			c_x += (1LL << i);
		}
		else if (is_in (c_x, c_y - (1LL << i), x, y, sum))
		{
			s += 'D';
			c_y -= (1LL << i);
		}
		else if (is_in (c_x - (1LL << i), c_y, x, y, sum))
		{
			s += 'L';
			c_x -= (1LL << i);
		}
	}
 
	return s;
}
 
int main ()
{
	cin >> n;
 
	for (ll i = 0; i < n; i++)
	{
		scanf ("%lld%lld", &x[i], &y[i]);
		if (i && abs (x[i] + y[i]) % 2 != abs (x[i-1] + y[i-1]) % 2)
		{
			cout << "-1";
			return 0;
		}
	}
 
	if ((x[0] + y[0]) % 2 == 0)
	{
		cout << 36 << endl;
		cout << 1 << ' ';
		even = 1;
	}
	else cout << 35 << endl;
 
	for (ll i = 34; i >= 0; i--)
		cout << (1LL << i) << ' ';
 
	for (ll i = 0; i < n; i++)
	{
		cout << find (x[i], y[i]) << endl;
	}
}
