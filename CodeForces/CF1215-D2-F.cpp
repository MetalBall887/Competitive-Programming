#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//Let's try to write every condition into 2-SAT form. Let x_i be true iff station i is emitted, f(j) - iff the signal power is at most j. Then, complaint condition
//for stations i and j can be written as x_i OR x_j, interference condition for stations i and j can be written as (NOT x_i) OR (NOT x_j), if l_i and r_i are 
//signal bounds for i-th station, then (NOT f(l_i - 1) OR NOT x_i) AND (f(r_i) OR NOT x_i) must be true as well. Also for f(i) to make sence for each i 
//f(i-1) OR (NOT f(i)) should also be true. Find if there is such vector x that satisfies all conditions with a usual 2-SAT algorithm.

using namespace __gnu_pbds;
 
#define N 2000003
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
int u[N], cl[N], n, m, p, M, ans[N];
 
vector <int> g[N], g_t[N], v;
 
void topsort (int x) {
	u[x] = 1;
	for (int to : g[x])
		if (!u[to]) topsort (to);
	v.push_back (x);
}
 
void scc (int x, int c) {
	cl[x] = c;
	for (int to : g_t[x])
		if (!cl[to]) scc (to, c);
}
 
void add_to_sat (int a, int b) {
	g[a ^ 1].push_back (b);
	g[b ^ 1].push_back (a);
	g_t[b].push_back (a^1);
	g_t[a].push_back (b^1);
}
 
int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
	cin >> n >> p >> M >> m;
 
	for (int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		x--, y--;
		add_to_sat (2 * x, 2 * y);
	}
 
	for (int i = 0; i < p; i++) {
		int l, r;
		cin >> l >> r;
		l--, r--;
 
		if (l) add_to_sat (2 * i + 1, 2 * (p + l - 1) + 1);
		add_to_sat (2 * i + 1, 2 * (p + r));
	}
 
	for (int i = 0; i < M - 1; i++) {
		add_to_sat (2 * (p + i) + 1, 2 * (p + i + 1));
	}
 
	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;
		x--, y--;
		add_to_sat (2 * x + 1, 2 * y + 1);
	}
 
	for (int i = 0; i < 2 * (p + M); i++)
		if (!u[i]) topsort (i);
 
	reverse (v.begin (), v.end ());
 
	int ptr = 0, sum = 0;
 
	for (int x : v) {
		if (!cl[x]) scc (x, ++ptr);
	}
 
	for (int i = 0; i < p + M; i++) {
		//if (!cl[2 * i]) continue;
		if (cl[2 * i] == cl[2 * i + 1]) {
			cout << -1;
			return 0;
		} else {
			ans[i] = (cl[2 * i] > cl[2 * i + 1]);
			if (i < p) sum += ans[i];
		}
	}
 
	ans[p + M - 1] = 1;
 
	cout << sum << ' ';
 
	for (int i = 0; i < M; i++) {
		if (ans[i + p]) {
			cout << i + 1 << endl;
			break;
		}
	}
 
	for (int i = 0; i < p; i++) {
		if (ans[i]) cout << i + 1 << ' ';
	}
}
