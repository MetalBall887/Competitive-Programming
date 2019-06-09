#include <iostream>
#include <cstdlib>
#include <string>
#include <set>
#include <map>
#include <algorithm>
//start a dfs from root to other vertices keeping a failure function of a prefix
//on a path between root and current vertex and count the number of occurences
//be careful with KMP implementation
#include <bitset>
#include <queue>
#include <math.h>
#include <stack>
#include <vector>
#include <string.h>
 
typedef long long ll;
 
const ll MOD = 1e9 + 7, INF = 1e18 + 1;
 
using namespace std;

vector <string> s[1000000];

vector <int> g[1000000];

string st, t;

int pf[1000000], ptr[1000000], kmp, new_ptr, n, gf[300000][26];

pair <int, int> expand (string & s, int cur)
{
	int ans = 0;

	for (char a : s)
	{
		cur = gf[cur][a - 'a'];

		if (cur == t.length ()) ans++;
	}

	return make_pair (ans, cur);
}

int dfs (int x, int p)
{
	int sum = 0;

	for (int i = 0; i < g[x].size (); i++)
		if (g[x][i] != p)
		{
			auto v = expand (s[x][i], ptr[x]);

			sum += v.first;
			ptr[g[x][i]] = v.second;

			sum += dfs (g[x][i], x);
		}

	return sum;
}

int main ()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 0; i < n - 1; i++)
	{
		string a;
		int p;

		cin >> p >> a;

		g[p-1].push_back (i + 1);
		s[p-1].push_back (a);
	}

	cin >> t;

	for (int i = 1; i < t.length (); i++)
	{
		int j = pf[i-1];

		while (j && (t[j] != t[i]))
			j = pf[j-1];

		pf[i] = j + (t[j] == t[i]);
	}

	gf[0][t[0] - 'a'] = 1;

	for (int i = 1; i <= t.length (); i++)
	{
		for (char c = 'a'; c <= 'z'; c++)
		{
			if (t[i] == c) gf[i][c - 'a'] = i + 1;
			else gf[i][c - 'a'] = gf[pf[i-1]][c - 'a'];
		}
	}

	cout << dfs (0, -1);
}
