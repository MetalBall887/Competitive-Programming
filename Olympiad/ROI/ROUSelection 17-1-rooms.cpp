#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//Let's take some cell from the room and check if it is inside the query rectangle. Then check if this room collides with
//the rectangle (there is a cell on a rectangle border). If none of that, the room is conpletely outside of the rectangle.
//So for a rectangle count the number of such pointer cells inside it with simple prefix sums and check the border if there
//are rooms that don't have pointer cells inside of the rectangle. Other rooms are completely outside of the rectangle.
 
using namespace __gnu_pbds;
 
#define N 2000001
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e6 + 7, MOD2 = 1e6 + 3;

int n, m, q;
int s[2001][2001], id[2001][2001], ptr;
int dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};
string a[2001];
bool used[5 * N];

struct point {
	int x, y;
} v[10 * N];

inline bool inside (point l, point a, point r) {
	return l.x <= a.x && a.x <= r.x && l.y <= a.y && a.y <= r.y;
}

void bfs (int x, int y, int col) {
	queue <point> q;
	q.push ({x, y});

	while (!q.empty ()) {
		point x = q.front ();
		q.pop ();
		id[x.x][x.y] = col;

		for (int i = 0; i < 4; i++) {
			if (x.x + dx[i] < 0 || x.x + dx[i] >= n) continue;
			if (x.y + dy[i] < 0 || x.y + dy[i] >= m) continue;
			if (id[x.x + dx[i]][x.y + dy[i]]) continue;
			if (a[x.x + dx[i]][x.y + dy[i]] != a[x.x][x.y]) continue;

			id[x.x + dx[i]][x.y + dy[i]] = col;
			q.push ({x.x + dx[i], x.y + dy[i]});
		}
	}
}

int main () {
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			s[i][j] = (i ? s[i-1][j] : 0) + (j ? s[i][j-1] : 0);
			if (i && j) s[i][j] -= s[i-1][j-1];
			if (!id[i][j]) {
				bfs (i, j, ++ptr);
				v[ptr] = {i, j};
				s[i][j]++;
			}
		}

	cin >> q;

	for (int i = 0; i < q; i++) {
		int lx, rx, ly, ry;
		cin >> lx >> ly >> rx >> ry;
		lx--, ly--, rx--, ry--;

		int ans = s[rx][ry] - (lx ? s[lx-1][ry] : 0) - (ly ? s[rx][ly-1] : 0);
		if (lx && ly) ans += s[lx-1][ly-1];

		for (int j = ly; j <= ry; j++) {
			if (!inside ({lx, ly}, v[id[lx][j]], {rx, ry}))
				used[id[lx][j]] = 1;

			if (!inside ({lx, ly}, v[id[rx][j]], {rx, ry}))
				used[id[rx][j]] = 1;
		}

		for (int j = lx + 1; j < rx; j++) {
			if (!inside ({lx, ly}, v[id[j][ly]], {rx, ry}))
				used[id[j][ly]] = 1;

			if (!inside ({lx, ly}, v[id[j][ry]], {rx, ry}))
				used[id[j][ry]] = 1;
		}

		for (int j = ly; j <= ry; j++) {
			ans += used[id[lx][j]]; 
			used[id[lx][j]] = 0;
			ans += used[id[rx][j]];
			used[id[rx][j]] = 0;
		}

		for (int j = lx; j <= rx; j++) {
			ans += used[id[j][ly]]; 
			used[id[j][ly]] = 0;
			ans += used[id[j][ry]];
			used[id[j][ry]] = 0;
		}

		cout << ans << endl;
	}
}
