#include <bits/stdc++.h>
//Basically complete search with optimisations. Transform this problem to minimal vertex cover with at most k vertices. 
//First, delete all vertices with degree at least k + 1, then we can prove that we can find the needed minimal vertex cover
//only when not more than k * (k + 1) vertices are left. Then, apply bruteforce.
 
using namespace std;
 
typedef long long ll;

const int N = 1e6 + 1;
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
int n, k, ok, m;
vector <int> g[N], l, ans;

int u[N];


void Rec (int idx, int k) {
	if (k < 0) return;
	if (idx == l.size ()) {
		ok = 1;
		vector <int> v;
		for (int i = 0; i < idx; i++) {
			if (!u[l[i]]) v.push_back (l[i]);
		}
		if (v.size () > ans.size ()) ans = v;
		return;
	}
	int x = l[idx];
	if (u[x]) return Rec (idx + 1, k - 1);

	u[x] = 1;
	Rec  (idx + 1, k - 1);
	u[x] = 0;

	vector<bool> cache;
	for (int to : g[x]) {
		cache.push_back (u[to]);
		u[to] = 1;
	}
	Rec (idx + 1, k);
	for (int i = 0; i < g[x].size (); i++) 
		u[g[x][i]] = cache[i];
}

int main() {
	ios::sync_with_stdio (0);

	cin >> n >> k; 
	cin >> m;
	k = n - k;

	
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		g[a-1].push_back (b - 1);
		g[b-1].push_back (a - 1);

	}

	for (int i = 0; i < n; i++) {
		sort (g[i].begin(), g[i].end());
		g[i].erase (unique (g[i].begin (), g[i].end ()), g[i].end ());
	}

	int removed = 0;
	for (int i = 0; i < n; i++) {
		if (!u[i] && g[i].size() > k) {
			u[i] = 1;
			removed++;
		}
	}

	for (int i = 0; i < n; i++) {
		if (u[i]) {
			g[i].clear ();
			continue;
		}

		vector <int> a;
		for (int to : g[i]) {
			if (!u[to]) a.push_back (to);
		}
		g[i] = a;
	}

	int num = 0;
	for (int i = 0; i < n; i++) {
		if (!u[i] && g[i].size() > 0) {
			num++;
			l.push_back (i);
		}
	}

	k -= removed;
	if (k < 0 || num > k * (k + 1)) {
		cout << "NIE";
		return 0;
	}

	Rec (0, k);

	if (!ok) cout << "NIE";
	else {
		for (int x : l) u[x] = 1;
		for (int x : ans) u[x] = 0;
		vector <int> print;
		for (int i = 0; i < n; i++) {
			if (!u[i]) print.push_back (i + 1);
		}
		cout << print.size () << endl;

		for (int x : print)
			cout << x << ' ';
	}

	return 0;
}
