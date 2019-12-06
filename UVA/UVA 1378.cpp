#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
//Let's play the nim, where an independent game is a stone. Now we can see a certain modification of a staircase nim with
//one stone.
#include <fstream>
#include <map>
#include <map>
#include <set>
#include <cstring>
#include <assert.h>
#include <cstdlib>
#include <cmath>
#include <queue>
 
using namespace std;
 
typedef long long ll;
 
const int INF = 1e9, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
const int N = 1e6;

int n, v[N], d[N];

int calc_mex (vector <int>& v) {
	sort (v.begin(), v.end());
	if (v.empty () || v[0]) return 0;

	for (int i = 1; i < v.size (); i++) {
		if (v[i-1] + 1 < v[i]) return v[i-1] + 1;
	}

	return v.back () + 1;
}

int main () {

	for (int k = 1; cin >> n; k++) {
		if (!n) break;
		for (int i = 1; i <= n; i++) {
			vector <int> v;
			for (int j = i - 1; j >= 0; j--)
				for (int k = j; k >= 0; k--) {
					v.push_back (d[j] ^ d[k]);
				}
			d[i] = calc_mex (v);
		}

		int ans = 0;

		for (int i = 0; i < n; i++) {
			cin >> v[i];

			if (v[i] & 1) ans ^= d[n - i - 1];
		}

		int a = -1, b = -1, c = -1;
		for (int i = 0; i < n && a == -1; i++) {
			if (!v[i]) continue;
			for (int j = i + 1; j < n && a == -1; j++)
				for (int k = j; k < n; k++) {
					if ((ans ^ d[n - 1 - i] ^ d[n - 1 - j] ^ d[n - 1 - k]) == 0) {
						a = i, b = j, c = k;
						break;
					}
				}
		}

		cout << "Game " << k << ": " << a << ' ' << b << ' ' << c << endl;
	}
}
