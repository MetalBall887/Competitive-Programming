#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//This problem is similar to Gaussian elimination. Let's name variables a, b, c, ... in ascending order and sort pairs.
//First one is a + b, second one is a + c and then there is an arbitrary number (O(n)) of a + c, a + d, ... and then b + c.
//So let's choose a position to be a b + c. Note that those three numbers define three equations of three variables, so we
//can uniquely determine a, b, c. After this, start eliminating from the start. Let's say, you eliminated all pairwise sums
//where maximal component is < x and you know all of the elements from a to x not including x. You know the smallest in
//remaining pairs will be a + x. Determine x, delete a + x, b + x, ... w + x from the set of pairwise sums. Implementing it
//with additional logarithmic factor may be slow, so you can optimise it by using a queue instead.

using namespace __gnu_pbds;
 
using namespace std;
 
typedef long long ll;

const int N = 1e6 + 1;
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

vector <int> v;
vector <vector <int>> ans;

int n;

void Rec (int a) {
	vector <int> l;
	l.push_back (a);
	queue <int> s;
	gp_hash_table<int, int> m, d;

	for (int i : v) {
		s.push (i);
		m[i]++;
	}


	while (!s.empty ()) {
		int t = s.front ();

		while (d[t]) {
			d[t]--;
			s.pop ();
			if (s.empty ()) break;
			t = s.front ();
		}

		if (s.empty ()) break;

		int nx = t - a;

		for (int x : l) {
			if (!m[nx + x]) return;
			m[nx + x]--, d[nx + x]++;
		}

		l.push_back (nx);
	}

	for (int i : v) {
		if (d[i]) return;
	}

	ans.push_back (l);
}
 
int main () {
	ios::sync_with_stdio (0);
	cin.tie (NULL);
	cin >> n;
	v.resize (n * (n - 1) / 2);
	for (int i = 0; i < n * (n - 1) / 2; i++) {
		cin >> v[i];
	}

	sort (v.begin(), v.end());

	for (int i = 2; i < n; i++) {
		if (i > 2 && v[i-1] == v[i]) continue;
		//a+b=v[0]	b-c=v[0]-v[1]
		//a+c=v[1]	2*b=v[2]+v[0]-v[1]
		//b+c=v[2]	
		if ((v[i] + v[0] + v[1]) % 2) continue;
		Rec (v[0] - (v[i] + v[0] - v[1]) / 2);
	}

	cout << ans.size () << endl;
	for (auto a : ans) {
		for (int x : a) {
			cout << x << ' ';
		}
		cout << '\n';
	}
}
