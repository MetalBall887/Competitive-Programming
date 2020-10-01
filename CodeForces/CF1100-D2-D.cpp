#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//First,let's move the king to the center. Divide the field into quarters, each rook attacks at least one square in 3 quarters. If the king decides to traverse 
//any quarter diagonally, the player will have to move all the rooks if they attack any square on the quarter. Now choose the quarter that has the most rooks
//attacking it. it will have at least 3*666/4 rooks attacking it which is about 500.25 and you can traverse a quarter diagonally in 500 turns, so he won't manage
//too take out all of his rooks. Be careful not to try to beat any rook.
 
using namespace __gnu_pbds;
 
#define N 2000001
 
using namespace std;
 
 
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
pair <int, int> p[1000];
 
int d[1000][1000];
 
bool move (int x, int y, int ox, int oy) {
	if (d[x][y]) {
		if (x != ox) x = ox;
		else y = oy;
	}
 
	assert (x != ox || y != oy);
	assert (abs (x - ox) <= 1 && abs (y - oy) <= 1);
 
	cout << x << ' ' << y << endl;
	fflush (stdout);
 
	int k = 2;
 
	cin >> k >> x >> y;
	d[p[k-1].first][p[k-1].second] = 0;
	if (k < 1) return false;
 
	p[k-1] = {x, y};
	d[x][y] = 1;
 
	return true;
}
 
 
int main () {
	int kx, ky;
	cin >> kx >> ky;
 
	for (int i = 0; i < 666; i++) {
		cin >> p[i].first >> p[i].second;
		d[p[i].first][p[i].second] = 1;
	}
 
	while (kx != 500 || ky != 500) {
		int dx = 0, dy = 0;
		if (kx > 500) dx = -1;
		if (kx < 500) dx = 1;
		if (ky > 500) dy = -1;
		if (ky < 500) dy = 1;
 
		if (!move (kx + dx, ky + dy, kx, ky)) return 0;
		kx += dx, ky += dy;
	}
 
	int w[4] = {0, 0, 0, 0};
 
	for (int i = 0; i < 666; i++) {
		int c = 0;
		if (p[i].first > 500) c += 2;
		if (p[i].second > 500) c++;
 
		w[c]++;
	}
 
	int c = 0;
 
	for (int i = 0; i < 4; i++)
		if (w[i] < w[c]) c = i;
 
	int dx = (c >= 2 ? -1 : 1), dy = (c % 2 ? -1 : 1), t = 499;
 
	while (t--) {
		if (!move (kx + dx, ky + dy, kx, ky)) return 0;
		kx += dx, ky += dy;
	}
 
	assert (0);
}
