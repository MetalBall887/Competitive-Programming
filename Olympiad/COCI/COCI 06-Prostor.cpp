#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//Let's perform a scanning plane method on one of coordinates. Since all rectangles are parallel to axis and have integer
//coordinates, we can succesfully approximize (without precision loss) them with 1xYxZ parallelograms and with 2d BIT remember
//which of them and where cross the scanning plane.

using namespace __gnu_pbds;
 
#define N 2000003
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
int n, k, m = 1000, p, q;

bool LD = true, RU = false;

struct BIT {
	int t[1000];

	void update (int x, int d) {
		for (; x < 1000; x = (x | (x + 1)))
			t[x] += d;
	}

	int get (int r) {
		int sum = 0;
		for (; r >= 0; r = (r & (r + 1)) - 1)
			sum += t[r];

		return sum;
	}

	int get (int l, int r) {
		return get (r) - get (l - 1);
	}
} l, r, u, d;

int nm = 0;

struct BIT2D {
	int t[1000][1000];
	int reverse_x, reverse_y;

	void update (int x, int y, int d) {
		if (reverse_x) x = m - x - 1;
		if (reverse_y) y = m - y - 1;
		for (int i = x; i < 1000; i = (i | (i + 1)))
			for (int j = y; j < 1000; j = (j | (j + 1)))
				t[i][j] += d;
	}

	int get (int x, int y) {
		if (reverse_x) x = m - x - 1;
		if (reverse_y) y = m - y - 1;
		int sum = 0;

		for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
			for (int j = y; j >= 0; j = (j & (j + 1)) - 1)
				sum += t[i][j];

		return sum;
	}
	BIT2D () {}
	BIT2D (int x, int y) : reverse_x (x), reverse_y (y) {}
} ld (0, 0), lu (0, 1), rd (1, 0), ru (1, 1);

int count_rectangles (int x1, int y1, int x2, int y2) {
	int sum = l.get (0, x1 - 1) + r.get (x2 + 1, m - 1);
	sum += d.get (0, y1 - 1) + u.get (y2 + 1, m - 1);
	sum -= ld.get (x1 - 1, y1 - 1) + lu.get (x1 - 1, y2 + 1);
	sum -= rd.get (x2 + 1, y1 - 1) + ru.get (x2 + 1, y2 + 1);
	return nm - sum;
}

void update_rectangle (int x1, int y1, int x2, int y2, int v) {
	nm += v;
	l.update (x2, v), r.update (x1, v);
	u.update (y1, v), d.update (y2, v);
	ld.update (x2, y2, v), lu.update (x2, y1, v); 
	rd.update (x1, y2, v), ru.update (x1, y1, v);
}

struct rect {
	int x1, y1, x2, y2, z, d;
	bool operator < (const rect& b) {
		return tie (z, d) < tie (b.z, b.d);
	}
};

vector <rect> v;

int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);

	cin >> n;

	for (int i = 0; i < n; i++) {
		int x1, y1, z1, x2, y2, z2;
		cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
		if (x1 > x2) swap (x1, x2);
		if (y1 > y2) swap (y1, y2);
		if (z1 > z2) swap (z1, z2);

		v.push_back ({x1, y1, x2, y2, z1, 1});
		v.push_back ({x1, y1, x2, y2, z2 + 1, -1});
	}

	sort (v.begin(), v.end());

	ll ans = 0;

	for (int i = 0; i < v.size (); i++) {
		if (v[i].d == 1) {
			ans += count_rectangles (v[i].x1, v[i].y1, v[i].x2, v[i].y2);
		}

		update_rectangle (v[i].x1, v[i].y1, v[i].x2, v[i].y2, v[i].d);
	}

	cout << ans;
}
