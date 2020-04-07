#include <bits/stdc++.h>
//Note that we can view the collide as "all ants colliding keep moving, ant moving to the left sums the color of the second ant
//to his own color". Now we can solve this problem with a scanning line, where for each ant moving to the left we will keep
//track of all ants colliding with it (grouped by color) until it fells off the bar. The other thing to keep in mind for ants 
//moving to the left is the time when they pass their last ant to count the distance walked till the end of the bar.
 
#define N 1000003
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

int n, d[50], K;
ll ans[50], L;
vector < pair <int, int> > vl, vr;

int main () {
	cin >> n >> K >> L;

	for (int i = 0; i < n; i++) {
		string c;
		int x, b;
		cin >> x >> b >> c;
		if (c == "D") {
			vr.push_back ({x, b});
		} else {
			vl.push_back ({x, b});
		}
	}

	int j = vl.size () - 1;

	for (int i = vr.size () - 1; i >= 0; i--) {
		ans[vr[i].second] += 2 * (L - vr[i].first);
		while (j >= 0 &&  vr[i].first < vl[j].first) {
			ans[vl[j].second] += abs (vr[i].first - vl[j].first);
			d[vl[j].second]++;
			j--;
		}

		int d2[50];

		for (int j = 0; j < K; j++) {
			d2[(j + vr[i].second) % K] = d[j];
		}

		if (i > 0) {
			int dist = vr[i].first - vr[i-1].first;
			for (int j = 0; j < K; j++) {
				d[j] = d2[j];
				ans[j] += (ll) d[j] * dist;
			}
		}
	}

	j = 0;
	int sum = 0;

	for (int i = 0; i < vl.size (); i++) {
		while (j < vr.size () && vr[j].first < vl[i].first) {
			sum += vr[j].second;
			j++;
		}

		int t = 2 * vl[i].first - max (0, vl[i].first - vr[0].first);
		ans[(vl[i].second + sum) % K] += t;
	}

	for (int i = 0; i < K; i++) {
		cout << ans[i] / 2;
		if (ans[i] & 1LL) cout << ".5";
		else cout << ".0";
		cout << '\n';
	}
}
