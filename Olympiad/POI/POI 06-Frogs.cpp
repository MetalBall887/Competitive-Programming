#include <bits/stdc++.h>
//As soon as we count the distance of the closest scarecrow to each point we can solve the problem in numerous ways as, for
//example, finding the MST. We can find the closest scarecrow by regrouping the equclidian square distance as 
//dy^2 + (i-j)^2 = dy^2+j^2-2ij+i^2, where dy^2 is minimum distance for scarecrows in j wrt only vertical lines. So if on 
//some row we for i want to find j such that this value is minimal, we should minimize fj(i) = kx+b, where k = -2j, 
//b = j^2 + dy^2. We can do it with Convex Hull Trick. Note that k and b do not depend on previous minima, so we can construct
//the hull offline and traverse it with the second pointer in O(n).
 
#define N 1000003
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

int wx, wy, n;

bitset<1001> sc[1001];
int d[1001][1001], p[N], px, py, kx, ky;
vector < pair <int, int> > e[N];

struct line {
	ll k, b;
} v[1001];

int ptr;

int find (int x) {
	if (p[x] == x) return x;
	return p[x] = find (p[x]);
}

void unite (int a, int b) {
	a = find (a), b = find (b);
	if (a == b) return;
	p[b] = a;
}

bool bad (line a, line b, line c) {
	return (b.b - a.b) * (c.k - b.k)  < (c.b - b.b) * (b.k - a.k);
}

void row_x (int x) {
	ptr = 0;
	for (int i = 0; i < wy; i++) {
		line b = {-2 * i, d[x][i] * d[x][i] + i * i};
		if (d[x][i] != N) {
			while (ptr >= 2 && bad (v[ptr-2], v[ptr-1], b))
				ptr--;
			v[ptr] = b, ptr++;
		}
	}

	int j = 0;

	for (int i = 0; i < wy; i++) {
		while (j < ptr - 1 && (v[j+1].b - v[j].b) <= i * (v[j].k - v[j+1].k)) {
			j++;
		}
		d[x][i] = v[j].k * i + v[j].b + i * i;
	}
}

int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cin >> wx >> wy;

	cin >> px >> py >> kx >> ky;
	px--, py--, kx--, ky--;

	cin >> n;

	for (int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		x--, y--;
		sc[x][y] = 1;
	}

	for (int i = 0; i < wx * wy; i++) {
		p[i] = i;
	}

	for (int j = 0; j < wy; j++) {
		int last = -1;
		for (int i = 0; i < wx; i++) {
			if (sc[i][j]) last = i;
			if (last == -1) d[i][j] = N;
			else d[i][j] = i - last;
		}

		last = -1;

		for (int i = wx - 1; i >= 0; i--) {
			if (sc[i][j]) last = i;
			if (last != -1) d[i][j] = min (d[i][j], last - i);
		}
	}

	for (int i = 0; i < wx; i++)
		row_x (i);

	for (int i = 0; i < wx; i++)
		for (int j = 0; j < wy; j++) {
			if (j < wy - 1) e[min (d[i][j], d[i][j+1])].push_back ({i * wy + j, i * wy + j + 1});
			if (i < wx - 1) e[min (d[i][j], d[i+1][j])].push_back ({i * wy + j, (i + 1) * wy + j});
		}

	for (int i = N - 1; i >= 0; i--) {
		for (auto a : e[i]) {
			unite (a.first, a.second);
		}

		if (find (px * wy + py) == find (kx * wy + ky)) {
			cout << min ({i, d[kx][ky], d[px][py]});
			return 0;
		}
	}

	assert (0);
}
