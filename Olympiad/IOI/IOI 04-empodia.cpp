#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//We have several conditions for a segment [l;r] to be a a framd sequence:
//1) a[r] - a[l] = r - l -> a[r]-r=a[l]-l
//2) There is no value in [l;r] larger than a[l]
//3) There is no value in [l;r] smaller than a[r]
//if both three conditions are fulfilled, in segment [l;r] there are elements [a[l];a[r]], where a[r]-a[l]+1=r-l+1, which
//means all values from a[l] to a[r] are inside this segment, also a[l] and a[r] are minimum and maximum.
//Notice that the first condition is easily handled by grouping by a[i]-i. Then for each x we find the rightmost element
//larger then a[x], which will be the left bound on l so [l;x] could be the segment. In the same way we can find the right 
//bound on r so [x;r] could be segment and try to match them with scanning line, where S is the set of current possible 
//right endpoints [l;x] (where l < current_x) and for the left endpoint we find the closest right endpoint from the set and
//in case it fits the bound, we have a new framed interval. Note that we might have found more but we need the closest since
//others will not be empodia. After this we have O(N) sorted empodio candidates and can find empodia in linear time.

using namespace __gnu_pbds;

#define N 2000001

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

int a[N], n;

int st[N], ptr;

set <int> s;

struct query {
	int l, r;

	bool operator < (const query& x) {
		if (l != x.l) return l < x.l;
		if ((r < 0) != (x.r < 0)) return (r < 0) < (x.r < 0);
		return abs (r) < abs (x.r);
	}
};

vector <query> v[2 * N];

vector <pair <int, int>> ans, new_ans;

int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	for (int i = n - 1; i >= 0; i--) {
		int x;
		while (ptr && a[st[ptr-1]] > a[i]) {
			ptr--;
		}
		if (!ptr) v[a[i]-i+n].push_back ({i, -(n + 1)});
		else v[a[i]-i+n].push_back ({i, -st[ptr-1]});
		st[ptr] = i;
		ptr++;
	}

	ptr = 0;

	for (int i = 0; i < n; i++) {
		int x;
		while (ptr && a[st[ptr-1]] < a[i]) ptr--;
		if (!ptr) v[a[i]-i+n].push_back ({-1, i});
		else v[a[i]-i+n].push_back ({st[ptr-1], i});
		st[ptr] = i;
		ptr++;
	}

	for (int i = 0; i <= 2 * n; i++) {
		sort (v[i].begin (), v[i].end ());

		for (auto a : v[i]) {
			if (a.r < 0) {
				int x;
				auto it = s.upper_bound (a.l);
				if (it != s.end ()) x = *it;
				else x = n + 1;
				if (x < -a.r) ans.push_back ({a.l, x});
			} else {
				s.insert (a.r);
			}
		}

		s.clear ();
		v[i].clear ();
	}

	sort (ans.begin (), ans.end ());
	int mn_r = n + 1;

	for (int i = ans.size () - 1; i >= 0; i--) {
		if (mn_r > ans[i].second) {
			new_ans.push_back (ans[i]);
			mn_r = ans[i].second;
		}

		ans.pop_back ();
	}

	ans = move (new_ans);
	reverse (ans.begin (), ans.end ());

	cout << ans.size () << endl;

	for (int i = 0; i < ans.size (); i++) {
		cout << ans[i].first + 1 << ' ' << ans[i].second + 1 << '\n';
	}
}
