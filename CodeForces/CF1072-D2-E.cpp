#include <iostream>
#include <cstdlib>
#include <string>
#include <set>
#include <stdio.h>
#include <map>
//Bruteforce prove some facts, precalculated transitions that fill fill some block with fixed size
//with zeroes (sometimes with changing bits on the right) then use this precalculation
#include <algorithm>
#include <bitset>
#include <queue>
#include <math.h>
#include <stack>
#include <vector>
#include <string.h>
 
typedef long long ll;
 
const ll MOD = 1e9 + 7, INF = 1e18;
 
using namespace std;

int bin = 9;

struct pr
{
	int x, y, z;
};

vector <pr> p[10000][10], p_end[10000][10], ans, g_p[10000][10], fl_p[10000][10];

pr diff (int a, int b)
{
	vector <int> v;

	pr s;

	for (int i = 0; i < bin; i++)
	{
		if ((a & (1 << i)) != (b & (1 << i)))
			v.push_back (i + 1);
	}

	s.x = v[0];
	s.y = v[1];
	s.z = v[2];

	return s;
}

vector <int> g[10000][10], fl[10000][10];

string to_st (int a)
{
	string s;

	for (int i = 0; i < bin; i++)
	{
		s += char (a % 2 + '0');
		a /= 2;
	}

	return s;
}

int to_int (string s)
{
	int a = 0;
	
	for (int i = s.length () - 1; i >= 0; i--)
	{
		a = a * 2 + s[i] - '0';
	}

	return a;
}

int u_end[1000000][10], u_fill[1000000][10];

void bfs_fill (int x)
{
	queue <int> q;

	q.push (x);

	while (!q.empty ())
	{
		int x = q.front ();
		q.pop ();

		u_fill[x][bin] = 1;

		for (int i = 0; i < g[x][bin].size (); i++)
		{
			int to = g[x][bin][i];
			if (!u_fill[to][bin])
			{
				u_fill[to][bin] = 1;
				q.push (to);
				p[to][bin] = p[x][bin];
				p[to][bin].push_back (g_p[x][bin][i]);
			}
		}
	}
}

void bfs_end (int x)
{
	queue <int> q;

	q.push (x);

	while (!q.empty ())
	{
		int x = q.front ();
		q.pop ();

		u_end[x][bin] = 1;

		for (int i = 0; i < fl[x][bin].size (); i++)
		{
			int to = fl[x][bin][i];
			if (!u_end[to][bin])
			{
				u_end[to][bin] = 1;
				q.push (to);
				p_end[to][bin] = p_end[x][bin];
				p_end[to][bin].push_back (fl_p[x][bin][i]);
			}
		}
	}
}



int main ()
{
	for (int f = 1; f <= 9; f++)
	{
		bin = f;
		for (int i = 0; i < (1 << bin); i++)
		{
			string b = to_st (i);

			for (int j = 0; j < bin; j++)
				for (int k = 1; k < bin + 9; k++)
					if (j + 2 * k < bin + 9)
					{
						string s = b;

						if (b[j] == '0') s[j] = '1';
						else s[j] = '0';
						if (b[j + k] == '0') s[j + k] = '1';
						else s[j + k] = '0';
						if (j + 2 * k < bin)
						{
							if (s[j + 2 * k] == '0') s[j + 2 * k] = '1';
							else s[j + 2 * k] = '0';

							fl[i][bin].push_back (to_int (s));
							fl_p[i][bin].push_back ({j, j + k, j + 2 * k});
							fl[to_int (s)][bin].push_back (i);
							fl_p[to_int (s)][bin].push_back ({j, j + k, j + 2 * k});
						}

						g[i][bin].push_back (to_int (s));
						g[to_int (s)][bin].push_back (i);
						g_p[i][bin].push_back ({j, j + k, j + 2 * k});
						g_p[to_int (s)][bin].push_back ({j, j + k, j + 2 * k});
					}
		}

		bfs_fill (0);
		bfs_end (0);
	}

	string s;

	int n;

	char a[10];

	cin >> n;

	for (int i = 0; i < n; i++)
	{
		scanf ("%s", a);
		s += a[0];
	}

	string d = s;

	if (n < 9)
	{
		if (!u_end[to_int (s)][n]) cout << "NO";
		else
		{
			int k = to_int (s);

			cout << "YES\n";

			cout << p_end[k][n].size () << endl;

			for (pr a : p_end[k][n])
			{
				printf ("%d %d %d\n", a.x + 1, a.y + 1, a.z + 1);
			}
		}

		return 0;
	}

	int ptr = 0;

	if (n % 9)
	{
		string k;

		for (int i = 0; i < n % 9; i++)
			k += s[i];

		int t = to_int (k);

		for (pr a : p[t][n % 9])
		{
			ans.push_back (a);
			s[a.x] = '0' ^ '1' ^ s[a.x];
			s[a.y] = '0' ^ '1' ^ s[a.y];
			s[a.z] = '0' ^ '1' ^ s[a.z];
		}

		ptr += n % 9;
	}

	for (int i = ptr; i < n - 9; i += 9)
	{
		string k;

		for (int i = ptr; i < ptr + 9; i++)
			k += s[i];

		int t = to_int (k);

		for (pr a : p[t][9])
		{
			pr b = {a.x + ptr, a.y + ptr, a.z + ptr};
			ans.push_back (b);
			s[b.x] = '0' ^ '1' ^ s[b.x];
			s[b.y] = '0' ^ '1' ^ s[b.y];
			s[b.z] = '0' ^ '1' ^ s[b.z];
		}

		ptr += 9;
	}


	string k;
	for (int i = ptr; i < n; i++)
		k += s[i];

	int t = to_int (k);

	for (pr a : p_end[t][9])
	{
		pr b = {a.x + ptr, a.y + ptr, a.z + ptr};
		ans.push_back (b);
		s[b.x] = '0' ^ '1' ^ s[b.x];
		s[b.y] = '0' ^ '1' ^ s[b.y];
		s[b.z] = '0' ^ '1' ^ s[b.z];
	}

	cout << "YES\n";

	cout << ans.size () << endl;

	string h;

	for (int i = 0; i < n; i++)
		h += '0';

	for (pr a : ans)
	{
		printf ("%d %d %d\n", a.x + 1, a.y + 1, a.z + 1);
		h[a.x] = '0' ^ '1' ^ h[a.x];
		h[a.y] = '0' ^ '1' ^ h[a.y];
		h[a.z] = '0' ^ '1' ^ h[a.z];
	}
}
