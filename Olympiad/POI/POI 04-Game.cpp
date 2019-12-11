#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <fstream>
//First of all, let's decide if we can win at all. This problem is a typical staircase nim one. If we take all vacant spots
//as borders of heaps, all pawns that go after each other will get into one heap, and from each heap an arbitrary number
//of pawns can be moved forward. We're losing as soon as we put any pawn on the cell before the last, giving our opponent
//a chance to win. So, as long as we don't have other moves, we simply do not do that because everything is more optimal
//than letting your opponent win in one move. Now it sounds like staircase nim. After we solve it, we should find the number
//of moves that lead to the losing position. Here we can try every non-empty heap and do some caseworking with the idea of:
//if we can delete/add to the valid nim heap, try to find the value we should add/delete so that overall xor will be 0 and
//chack if we can do this.
#include <map>
#include <memory>
#include <unordered_map>
#include <set>
#include <cstring>
#include <assert.h>
#include <cstdlib>
#include <cmath>
#include <queue>
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e9, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
const ll N = 1e6;

int n, a[N], m, pos[N], sz[N], pr[N];

int main () {
	ios::sync_with_stdio (false);
	cin.tie (NULL);
	cin >> m >> n;

	int xr = 0, heap = 0, dist = 0;
	vector < pair <int, int> > v;

	int p = 0;

	for (int i = 0; i < n; i++) {
		cin >> a[i];
		a[i]--;

		if (i && a[i-1] + 1 < a[i]) {
			v.push_back ({a[p], a[i-1]});
			p = i;
		}
	}

	v.push_back ({a[p], a[n-1]});

	int comp = 0;

	for (int i = 0; i < v.size (); i++) {
		auto a = v[i];
		if (!i) comp += a.first;
		else comp += a.first - v[i-1].second - 1;

		pos[i] = comp;
		sz[i] = a.second - a.first + 1;
	}

	if (a[n-1] == m - 2) {
		cout << sz[v.size () - 1];
		return 0;
	}

	comp += m - a[n-1] - 1;
	int ans = 0;

	for (int i = 0; i < v.size (); i++) {
		pr[i] = comp - pos[i] - 2;
		if (pr[i] & 1) ans ^= sz[i];
	}

	if (!ans) {
		cout << 0;
		return 0;
	}

	int cnt = 0;

	for (int i = 0; i < v.size (); i++) {
		if (pr[i] & 1) {
			if ((ans ^ sz[i]) <= sz[i]) {
				cnt++;
			}
		} else {
			if (!pr[i]) continue;
			if (i == v.size () - 1 || pr[i] - 1 != pr[i+1]) {
				if (ans <= sz[i]) cnt++;
			}
			else if ((ans ^ sz[i+1]) > sz[i+1] && 
				(ans ^ sz[i+1]) <= sz[i+1] + sz[i]) {
				cnt++;
			}
		}
	}

	cout << cnt;
}
