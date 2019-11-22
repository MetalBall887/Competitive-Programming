#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <fstream>
#include <map>
#include <unordered_map>
//One important limit is, top of 2x2 rectangles must be even. That means, we can divide everything to 2xN rows, the 
//games on them are independent. One such row is of size at most 20, so we can do the bitmask solution
#include <set>
#include <cstring>
#include <assert.h>
#include <cstdlib>
#include <cmath>
#include <queue>
#include <ext/pb_ds/assoc_container.hpp>
 
using namespace __gnu_pbds;
 
#define N 1000000
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e9, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

int d[2000][2000], u[2000][2000];

class LittleSquares {
	int in_bit (string s) {
		int b = 0;
		for (int i = 0; i < s.length (); i++) {
			if (s[i] == '.') b += (1 << i);
		}

		return b;
	}
	int calc_mex (vector <int> v) {
		sort (v.begin (), v.end ());

		if (v[0] || v.empty ()) return 0;
		for (int i = 1; i < v.size (); i++) {
			if (v[i-1] + 1 < v[i]) return v[i-1] + 1;
		}

		return v.back () + 1;
	}

	int f (int l, int r) {
		if (l <= r) return d[l][r];
		else return 0;
	}
public:
	int row (int p, int q, int n) {
		if (u[p][q]) return d[p][q];
		u[p][q] = 1;

		if (!p && !q) return 0;

		vector <int> v;

		for (int i = 0; i < n; i++) {
			if (p & (1 << i)) v.push_back (row (p - (1 << i), q, n));
			if (q & (1 << i)) v.push_back (row (p, q - (1 << i), n));
		}

		for (int i = 0; i < n - 1; i++) {
			int a1 = p & (1 << i);
			int a2 = p & (1 << (i + 1));
			int a3 = q & (1 << i);
			int a4 = q & (1 << (i + 1));

			if (a1 && a2 && a3 && a4) 
				v.push_back (row (p - (1 << i) - (1 << (i + 1)), q - (1 << i) - (1 << (i + 1)), n));
		}

		return d[p][q] = calc_mex (v);
	}

	string winner (vector <string> s) {

		int ans = 0, n = s[0].length ();
		for (int i = 0; i < s.size (); i += 2) {


			ans ^= row (in_bit (s[i]), in_bit (s[i+1]), n);
		}

		if (ans) return "first";
		return "second";
	}
};
