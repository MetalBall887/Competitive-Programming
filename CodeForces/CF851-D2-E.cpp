#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <fstream>
#include <map>
//The main idea here is that we can process prime divisors independently. For a state for every divisor we should know
//if there is a p^n as a divisor somewhere or there isn't. Since n can't be big, we can use bitmasks. Our operation is
//taking bits higher than some x and "pull" them down, conjucting them with lower bits. For each divisor we have one fixed
//original state and some set of possible sequences of operations that shouldn't all lead to different states. 
//Practically, the number of such states is not big. Let's call xi the number of different states of max.power i. Obviously, 
//for each i = 0..m/2 xi is O(2^(m/2)). For i > m / 2 for every pair of bitmasks of the states there exists a common prefix
//of size i - (m - i) = 2i-m and the differing suffix is of size (m - i) with i > m / 2, so we can bound the overall number of
//states by O(m2^(m/2)). Count sprague-grundy numbers on such graph.
#include <unordered_map>
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

map < int, vector <int> > m;

int n, a[N];

void factorize (int x) {
	int s = a[x];
	for (int i = 2; i * i <= a[x]; i++) {
		if (a[x] % i) continue;
		int c = 0;
		while (s % i == 0) {
			c++;
			s /= i;
		}

		m[i].push_back (c);
	}

	if (s != 1) {
		m[s].push_back (1);
	}
}

int grundy (vector <int> v) {
	sort (v.begin(), v.end());
	vector <int> t;

	for (int i : v)
		if (t.empty () || t.back () != i)
			t.push_back (i);

	vector <int> d (t.back ());

	d[t.back ()] = 0;

	int ptr = t.size ();

	for (int i = t.back () - 1; i >= 0; i--) {
		int mx = mex (d[i]);

		for (int j = i - 1; j >= (ptr ? d[ptr-1] : 0); ptr--)
	}
}

int main () {
	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> a[i];

		factorize (i);
	}
}
