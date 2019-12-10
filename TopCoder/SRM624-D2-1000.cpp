#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <fstream>
#include <map>
//Whenever the segmeny is put, it divides a polygon into
//two parts and two more vertices can't be used anymore, so we can divide our Sprague-Grundy heap
#include <memory>
#include <unordered_map>
#include <set>
#include <cstring>
#include <assert.h>
#include <cstdlib>
#include <cmath>
#include <queue>
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e9, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
const ll N = 1e6;

struct GameOfSegments {
	int calc_mex (vector <int>& v) {
		sort (v.begin(), v.end());
	 
		if (v.empty () || v[0]) return 0;
		for (int i = 0; i < v.size () - 1; i++) {
			if (v[i] + 1 < v[i+1]) return v[i] + 1;
		}
	 
		return v.back () + 1;
	}

	bool winner (int n) {
		vector <int> d (n + 1);

		for (int i = 2; i <= n; i++) {
			vector <int> v;
			for (int j = 0; j <= i - 2; j++) {
				int l = j, r = i - 2 - j;
				v.push_back (d[l] ^ d[r]);
			}
	 
			d[i] = calc_mex (v);
			cout << d[i] << endl;
		}

		return d[n];
	}
}
