#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//Let's solve the task in reverse order. The last item added to the depot is the last in some row. Construct an operation, 
//inversed to addition operation from statement: if the added item is not in the first row, there was an iten with smaller 
//index to push him but with index big enough not to push any elements smaller. Therefore, we need to find the biggest smaller
//index in the row above. If there is none (all indices are bigger), such operation wasn't possible. 

using namespace __gnu_pbds;

#define N 2000001

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

int n;

vector <int> q;

struct state {
	vector <vector <int>> v;

	vector <int>& operator[] (int x) {
		return v[x];
	}

	void print () {
		for (auto a : v) {
			for (auto x : a)
				cout << x << ' ';
			cout << endl;
		}

		cout << endl;
	}

	bool empty () {
		for (auto a : v)
			if (a.size ()) return false;
		return true;
	}

} root;

bool placeable (state& a, int last) {
	if (a[last].empty ()) return false;
	int x = *a[last].rbegin ();
	for (int i = last - 1; i >= 0; i--) {
		if (a[i].empty ()) return false;
		auto k = lower_bound (a[i].begin(), a[i].end(), x);
		if (k == a[i].begin ()) return false;
		x = *(--k);
	}

	return true;
}

int backward (state& a, int last) {
	auto k = a[last].end ();
	k--;
	int x = *k;
	a[last].erase (k);
	for (int i = last - 1; i >= 0; i--) {
		k = lower_bound (a[i].begin(), a[i].end(), x);
		k--;
		swap (x, *k);
	}

	return x;
}

void forward (state& a, int val) {
	for (int i = 0; i < a.v.size (); i++) {
		if (a[i].empty () || *a[i].rbegin () < val) {
			a[i].push_back (val);
			break;
		}
		auto k = upper_bound (a[i].begin(), a[i].end(), val);
		swap (*k, val);
	}
}

void Rec (state& a) {
	if (a.empty ()) {
		for (auto it = q.rbegin (); it < q.rend (); it++)
			cout << *it << ' ';
		cout << '\n';
		return;
	}

	for (int i = 0; i < a.v.size (); i++) {
		if (placeable (a, i)) {
			q.push_back (backward (a, i));
			Rec (a);
			forward (a, q.back ());
			q.pop_back ();
		}
	}
}



int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cin >> n;

	for (int i = 0; i < n; i++) {
		root.v.push_back (vector <int> ());

		int h;
		cin >> h;

		while (h--) {
			int x;
			cin >> x;
			root[i].push_back (x);
		}
	}

	Rec (root);
}
