#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//last[i] - the last time number i was requested. We simply simulate the process but also keep a queue where, since time always increases, all elements
//are sorted by last[]. That means, if we are to delete the number, we should delete it from the front of the queue. But each cache hit for i changes last[i]
//in this case we create a duplicate in the queue. Duplicates are handled easily by ignoring and deleting all of them except the last one. 
//The complexity is O(n|cmds|) amortized.
 
using namespace __gnu_pbds;
 
#define N 2000003
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

int n, sz[30], cur_sz, uniq;

int last[1 << 24], s[1 << 24];

vector <int> ans[N];

struct query {
	int t;
	int a, b, n;
};

vector <query> q;

struct cache {
	pair <int, int> data[(int) 2e7];
	int l, r;
	pair <int, int> front () {
		return data[l];
	}

	bool empty () {
		return l == r;
	}

	void pop () {
		l++;
	}

	void push (const pair <int, int>& b) {
		data[r++] = b;
	}

	void fit () {
		if (r < 1e7) return;

		for (int i = l; i < r; i++) {
			data[i-l] = data[i];
		}
		r -= l;
		l = 0;
	}
} cache;

int cache_check (int x, int t) {
	if (s[x]) {
		last[x] = t;
		cache.push ({x, t});
	}
	else {
		while (!cache.empty () && cache.front().second < last[cache.front().first]) 
			cache.pop ();

		if (uniq + 1 > cur_sz) {
			s[cache.front().first] = 0;
			cache.pop ();
			uniq--;
		}

		cache.push({x, t});
		s[x] = 1;
		last[x] = t;
		uniq++;

		return 1;
	}

	return 0;
}

int main () {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> sz[i];
	}

	string type;

	while (cin >> type && type != "END") {
		if (type == "ADDR") {
			int a; cin >> a;
			q.push_back ({0, a, 0, 0});
		} else if (type == "RANGE") {
			int a, b, n; cin >> a >> b >> n;
			q.push_back ({1, a, b, n});
		} else {
			q.push_back ({2, 0, 0, 0});
		}
	}

	int ptr = 0, miss = 0;

	for (int c = 0; c < n; c++) {
		ptr = 0, uniq = 0, cur_sz = sz[c];
		for (query a : q) {
			if (a.t == 0) {
				miss += cache_check (a.a, ptr);
			} else if (a.t == 1) {
				for (int i = 0; i < a.n; i++)
					miss += cache_check (a.a + a.b * i, ptr);
			} else {
				ans[ptr].push_back (miss);
				miss = 0;
			}
			ptr++;
			cache.fit();
		}

		while (!cache.empty ()) {
			s[cache.front().first] = 0;
			cache.pop();
		}
	}

	for (int i = 0; i < ptr; i++) {
		if (!ans[i].size ()) continue;
		cout << ans[i][0];
		for (int j = 1; j < n; j++)
			cout << ' ' << ans[i][j];
		cout << '\n';
	}
}
