#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//f[x] - answer to the problem if x is a mask representing a city in each bit and the bit is 1 if there is a judge. As a transition we can try taking any judge
//and moving to some other city by the shortest path but we will not have a good ordering and the graph representing states and transitions will not be DAG.
//Another way of transition is to take a pair of judges and move them to some one city by shortest paths. That way transitions are directed towards states where
//the number of cities with judges in it is smaller by 1, so the ordering is preserved. The number of different such moves from one state is O(N^3) but we can 
//speed it up by dividing the transition into two phases: we move first judge to some city then we move some other judge to this city, and store the result
//of the first pase in d[x][i] - the answer for mask x where the first phase of a transition occured and the judge stopped in city i. After this the complexity
//of the solution will be O(N^2*2^N).
 
//using namespace __gnu_pbds;
 
#define N 2000001
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

int p[1 << 20][20];

pair <int, int> pf[1 << 20];

vector <int> bt[21];
vector < pair <int, int> > g[20];

pair <ll, int> d[1 << 20][20], f[1 << 20]; 
ll dist[20][20], p_dist[20][20], n, m, dc, t;
 
inline bool has_bit (int a, int i) {
	return ((a >> i) & 1);
}

void show_path (int a, int b) {
	while (a != b) {
		cout << a + 1 << '-';
		a = p_dist[a][b];
	}
}

void solve () {
	cin >> dc >> m;

	dc--;

	fill (g, g + n, vector < pair <int, int> > ());

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			dist[i][j] = 1e18;

	for (int i = 0; i < n; i++)
		dist[i][i] = 0;

	for (int i = 0; i < m; i++) {
		int x, y, w;

		cin >> x >> y >> w;
		x--, y--;

		dist[x][y] = dist[y][x] = w;

		g[x].push_back ({y, w});
		g[y].push_back ({x, w});
	}

	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				dist[i][j] = min (dist[i][j], dist[i][k] + dist[k][j]);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			for (auto to : g[i])
				if (dist[to.first][j] + to.second == dist[i][j]) {
					p_dist[i][j] = to.first;
					break;
				}

	for (int i = 0; i < n; i++) {
		f[1 << i] = {dist[i][dc], 0};
		pf[1 << i] = {i, dc};
	}

	int k, bm = 0;

	cin >> k;

	for (int i = 2; i <= k; i++) {
		for (int x : bt[i]) {
			if (x >= (1 << n)) break;
			for (int a = 0; a < n; a++) {
				if (!has_bit(x, a)) continue;
				d[x][a] = {1e18, 0};
				for (int b = 0; b < n; b++) {
					if (!has_bit(x, b) || a == b) continue;
					auto c = f[x - (1 << b)];
					c.first += dist[a][b]; c.second++;
					if (d[x][a] > c) {
						d[x][a] = c;
						p[x][a] = b;
					}
				}

			}
		}

		for (int x : bt[i]) {
			if (x >= (1 << n)) break;
			f[x] = {1e18, 0};
			for (int a = 0; a < n; a++) {
				if (!has_bit(x, a)) continue;
				if (f[x] > d[x][a]) {
					f[x] = d[x][a];
					pf[x] = {a, a};
				}
			}

			for (int a = 0; a < n; a++) {
				if (!has_bit(x, a)) continue;
				for (int b = 0; b < n; b++) {
					if (has_bit(x, b)) continue;
					auto c = d[x - (1 << a) + (1 << b)][b];
					c.first += dist[a][b]; c.second++;
					if (f[x] > c) {
						f[x] = c;
						pf[x] = {a, b};
					}
				}
			}
		}

		//cout << i << endl;

	}

	vector <int> st(k);

	for (int i = 0; i < k; i++) {
		int x;
		cin >> x; x--;
		st[i] = x;

		bm |= (1 << x);
	}

	vector <int> to (n);

	int x = bm, y = __builtin_popcount(bm);

	while (y > 1) {
		int a = pf[x].first, b = pf[x].second;
		to[a] = b;
		
		x -= (1 << a);
		x += (1 << b);

		a = p[x][b];
		to[a] = b;
		
		x -= (1 << a);
		y--;
	}

	for (int i = 0; i < n; i++)
		if ((1 << i) & x) to[i] = dc;

	cout << "Case " << t << ": " << "distance = " << f[bm].first << endl;
	for (int i = 0; i < k; i++) {
		cout << "   ";
		while (st[i] != dc) {
			show_path (st[i], to[st[i]]);

			st[i] = to[st[i]];
		}

		cout << dc + 1 << '\n';
	}
	cout << '\n';
}

int main () {
	for (int i = 1; i < (1 << 20); i++) {
		bt[__builtin_popcount(i)].push_back(i);
	}


	while (cin >> n && n != -1) {
		t++;
		solve ();
	}
}
