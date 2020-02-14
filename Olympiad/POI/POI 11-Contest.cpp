#include <bits/stdc++.h>
 //We construct a bipartite graph, where left part are particpants and right part are problems. There is an edge (a, b).
 //when a person a can solve the problem b. We need to distribute the number of problems that way, the sum of squares of numbers
 //of problems is minimized (from the formula p(x) = r * n * (n + 1) / 2 we can extract r / 2 and n^2 + n will be left, 
 //where the sum of n will be fixed). For that we need to distribute problems as evenly as possible. For that we add one 
 //problem to each person by layers by finding augmenting paths, with which we could increase the degree by one without 
 //changing any other degrees. Proving can be done by pretending there are min (m, t / r) nodes for each "problem slot" for 
 //a person and then launching vertex-weighted min-cost maximal matching with Kuhn's, which is proven by matroid intersection.
 
using namespace std;
 
typedef long long ll;
 
const int N = 1e6 + 1;
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
const int inf = 1e9;
 
int p[1000], u[1000], u_p[1000], bl[1000];
int cnt[1000], n, m, r, k, t, t_m, c, sum;
vector <int> g[1000];
vector < pair <int, int> > ans[1000];
 
bool kuhn (int x) {
	if (u[x] == t_m) return false;
	u[x] = t_m;
 
	for (int to : g[x]) {
		if (u_p[to] == t_m) continue;
		u_p[to] = t_m;
		if (p[to] == -1 || kuhn (p[to])) {
			p[to] = x;
			return true;
		}
	}
 
	return false;
}
 
int main () {
	ios::sync_with_stdio (false);
	cin >> n >> m >> r >> t >> k;
	memset (p, -1, m * sizeof (p[0]));
	for (int i = 0; i < k; i++) {
		int a, b;
		cin >> a >> b;
		g[a-1].push_back (b - 1);
	}
 
	for (int i = 0; i < min (m, t / r); i++) {
		for (int x = 0; x < n; x++) {
			if (bl[x]) continue;
			t_m++;
			bl[x] = !kuhn (x);
		}
	}
 
	for (int i = 0; i < m; i++) {
		if (p[i] != -1) {
			ans[p[i]].push_back ({i, cnt[p[i]] * r});
			cnt[p[i]]++;
			c++, sum += cnt[p[i]] * r;
		}
	}
 
	cout << c << ' ' << sum << endl;
 
	for (int i = 0; i < n; i++) {
		for (auto a : ans[i]) {
			cout << i + 1 << ' ' << a.first + 1 << ' ' << a.second << '\n';
		}
	}
}
