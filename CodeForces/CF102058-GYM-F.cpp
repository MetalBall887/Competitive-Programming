#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <fstream>
#include <map>
#include <unordered_map>
#include <set>
//Game ends as soon as you put a diagonal that shares side with an another diagonal, because your opponent will have a
//chance to complement these two incident edges to a triangle. That means, whenever diagonal is put, it divides a polygon into
//two parts and two more vertices can't be used anymore
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
 
int d[5001], n;
 
int calc_mex (vector <int>& v) {
	sort (v.begin(), v.end());
 
	if (v[0]) return 0;
	for (int i = 0; i < v.size () - 1; i++) {
		if (v[i] + 1 < v[i+1]) return v[i] + 1;
	}
 
	return v.back () + 1;
}
 
int main () {
 
	for (int i = 2; i <= 5000; i++) {
		vector <int> v;
		for (int j = 0; j <= i - 2; j++) {
			int l = j, r = i - 2 - j;
			v.push_back (d[l] ^ d[r]);
		}
 
		d[i] = calc_mex (v);
	}
 
	int t;
 
	cin >> t;
 
	while (t--) {
		cin >> n;
 
		if (d[n]) cout << "First\n";
		else cout << "Second\n";
	}
}
