#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <set>
//Let's first count the number of different tables. In each hand there might be 8 cards with ranks 0-4. Order doesn't matter
//so for each rank we keep the number of cards in hand with such rank. Each array of size 5 and sum 8 fits. It is C[13][8]
//or ~500 and the number of different tables is this value squared. That's enough to make our program work in O(nlogn).
//We bruteforce all transitions and do a game bfs on a graph.
#include <bitset>
#include <cstring>
#include <map>
#include <cassert>
#include <cstdlib>
#include <cmath>
#include <queue>

#define N 1000000
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e9, MOD = 1e9 + 7, MOD2 = 1e6 + 2;

struct state {
	vector <int> a, b;
	ll num;

	state (vector <int> p, vector <int> q) {
		a.resize (5);
		b.resize (5);
		for (int i = 0; i < 5; i++) {
			a[i] = p[i];
			b[i] = q[i];
		}

		num = 0;
		for (int i = 0; i < 5; i++) {
			num = num * 81 + a[i] * 9 + b[i];
		}
	}

	state () {
		a.resize (5);
		b.resize (5);
	}

	bool operator < (const state& b) const {
		return num < b.num;
	}
} st[300000];

map <state, int> mp;

bool w[N], l[N], u[N];

queue <int> win, lose;

int ptr, n, d[N];

vector <int> g[N];

vector < vector <int> > v;

void generate (int step, vector <int> asl, int sum) {
	if (step == 5) {
		if (sum == 8) {
			v.push_back (asl);
		}
		return;
	}

	for (int i = 0; i + sum <= 8; i++) {
		asl.push_back (i);
		generate (step + 1, asl, sum + i);
		asl.pop_back ();
	}
}

int main () {
	generate (0, vector <int> (), 0);

	for (auto a : v)
		for (auto b : v) {
			mp[state (a, b)] = ptr++;
			st[ptr-1] = state (a, b);
		}

	for (int i = 0; i < ptr; i++) {
		vector <int> p = st[i].a;
		vector <int> q = st[i].b;

		if (p[0] == 8) continue;

		if (q[0] == 8) {
			l[i] = true;
			lose.push (i);
			continue;
		}

		for (int j = 0; j < 5; j++)
			for (int k = 0; k < 5; k++)
				if (p[j] && q[k] && (j && k)) {
					p[j]--;
					p[(j + k) % 5]++;
					g[mp[state (q, p)]].push_back (i);
					d[i]++;
					p[j]++;
					p[(j + k) % 5]--;
				}
	}

	while (!lose.empty () || !win.empty ()) {
		while (!lose.empty ()) {
			int x = lose.front ();
			lose.pop ();
			for (int to : g[x]) {
				if (u[to]) continue;
				u[to] = 1;
				w[to] = true;
				win.push (to);
			}
		}

		while (!win.empty ()) {
			int x = win.front ();
			win.pop ();
			for (int to : g[x]) {
				if (u[to]) continue;
				d[to]--;
				if (d[to] == 0) {
					u[to] = 1;
					l[to] = true;
					lose.push (to);
				}
			}
		}
	}

	int t;

	cin >> t;

	while (t--) {
		int f;

		scanf ("%d", &f);
		vector <int> p (5), q (5);
		for (int i = 0; i < 8; i++) {
			int x;
			scanf ("%d", &x);
			p[x]++;
		}

		for (int i = 0; i < 8; i++) {
			int x;
			scanf ("%d", &x);
			q[x]++;
		}

		if (f == 0) {
			if (w[mp[state (p, q)]]) cout << "Alice\n";
			else if (l[mp[state (p, q)]]) cout << "Bob\n";
			else cout << "Deal\n";
		}
		else {
			if (w[mp[state (q, p)]]) cout << "Bob\n";
			else if (l[mp[state (q, p)]]) cout << "Alice\n";
			else cout << "Deal\n";
		}
	}
}
