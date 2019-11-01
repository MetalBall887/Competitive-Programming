#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <fstream>
#include <set>
//First, let's differentiate games by n. If n is odd, all your moves will contain the odd number of stones, so
//parity of sum of all heaps decides. If n is even, we can take the even number of stones but the limited
//number of times. Basically, we have three possibilities: taking a stone from a non-minimal heap, taking
//a stone from a minimal heap or take one stone from each heap. Key is, the position, where the minimal heap
//is of even size and the total number of stones is even is losing. Whatever the current player will do, we can
//repeat his move: for the first type the number of stones we can pull from a heap not making it lesser than 
//minimum is sum - min_heap*n, which is an even number, so the second player will always be able to repeat
//second type - the minimal is even, third is also because the size of the smallest heap is even. Now
//what about winning positions? We can see that any other position is winning, because for odd sum and
//even minimum we can do the first type, for odd sum and odd minimum we can do the second type, for
//even sum and odd minimum we can do the third type and it will always lead to a losing position described
//above.
#include <bitset>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <cmath>
#include <queue>

#define N 1000000
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e9, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

ll n, sum, mn = 1e9;

int main () {
	int t;
	cin >> t;

	while (t--) {
		cin >> n;
		sum = 0, mn = 1e9;

		for (int i = 0; i < n; i++) {
			ll s;
			cin >> s;
			mn = min (mn, s);
			sum += s;
		}

		if (n & 1) {
			if (sum & 1) cout << "Yalalov";
			else cout << "Shin";
		}
		else {
			if ((sum & 1) || (mn & 1)) cout << "Yalalov";
			else cout << "Shin";
		}
		cout << endl;
	}
}
