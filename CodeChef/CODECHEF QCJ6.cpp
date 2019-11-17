#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <fstream>
#include <map>
#include <unordered_map>
#include <set>
#include <cstring>
//Notice that every coin is a heap.
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

int n, x, s;

int main () {
	cin >> n;
	while (n--) {
		cin >> s;
		x = 0;
		for (int i = 1; i <= s; i++) {
			int a;
			cin >> a;
			if (a & 1) x ^= i;
		}

		if (x) cout << "Tom Wins\n";
		else cout << "Hanks Wins\n";
	}

	return 0;
}
