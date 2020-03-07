#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//Finding distance between two points is just caseworking. Since an obelisk only falls down the graph is DAG so we can use
//dynamic programming. d[i][j] - the shortest path from the start to the j-th hole on i-th level. By calculating the distance
//between two points we can kiss the case where the ibelisk falls down in the middle of this path but this is ok because that
//means there is a prefix of this path that in the same number of moves will push you lower by at least one floor, so the edge
//we use now has the alternative, probably even more optimal one

using namespace __gnu_pbds;

#define N 2000001

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

int dx[3] = {-1, 1, 0};

struct Pt {
	ll x, y;
} S, E;

int n, m;

vector <Pt> p[N];
vector <ll> d[N];

ll dist (Pt a, Pt b) {
	ll x = abs (a.x - b.x), y = abs (a.y - b.y);
	if(m == 1) return abs (x) + abs (y);
	int ans = 1e9;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int g = 0; g < 2; g++)
			{
				for (int h = 0; h < 2; h++)
				{
					int p = abs (x + dx[i] * (m + 1));
					int q = abs (y + dx[j] * (m + 1));
					int t1 = p / (m + 1) + (i < 2);
					int t2 = q / (m + 1) + (j < 2);
					int cur = t1 * 2 + t2 * 2 + g * 2 + h * 2;
					p %= (m + 1);
					q %= (m + 1);
					if(p)
					{
						if (!t2) cur += 2;
						if (g) cur += m + 1 - p;
						else cur += p;
					}
					if(q)
					{
						if(!t1) cur += 2;
						if(h) cur += m + 1 - q;
						else cur += q;
					}
					ans = min (ans, cur);
				}
			}
		}
	}
	return ans;
} 

int main () {
	cin >> n >> m;

	cin >> S.x >> S.y >> E.x >> E.y;

	d[0].push_back (0);
	p[0].push_back (S);

	for (int i = 1; i < n; i++) {
		int h;
		cin >> h;
		d[i].resize (h);
		p[i].resize (h);

		for (int j = 0; j < h; j++) {
			cin >> p[i][j].x >> p[i][j].y;
			d[i][j] = INF;

			for (int k = 0; k < p[i-1].size (); k++) {
				d[i][j] = min (d[i][j], d[i-1][k] + dist (p[i-1][k], p[i][j]));
			}
		}
	}

	ll ans = INF;

	for (int i = 0; i < p[n-1].size (); i++) {
		ans = min (ans, d[n-1][i] + dist (p[n-1][i], E));
	}

	cout << (ans == INF ? -1 : ans);
}
