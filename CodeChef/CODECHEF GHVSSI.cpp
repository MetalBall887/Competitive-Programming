#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <fstream>
#include <map>
#include <memory>
#include <set>
//The idea of O(N^4) solution is simpler: Z can't be represented as a^2-b^2, when there is an odd number of 2 in his factorization
//Which means Z = 4k + 2 for integer k. So we track only Z % 4 and reduce the whole table to the # of elements with % 4 = k for k 
//k = 0..3. For O(N^3) we have to analyze the game and find that zero is not as useful when there is an even numbers of zeroes.
//Whenever you're in the losing position considering only elements not dividable by 4, you can take one dividable and "turn the
//table". Of course, your opponent will be able to do that too, so the table will be turned if only there is an odd number of
//dividable elements. In other case, such numbers give to a losing player nothing.
#include <cstring>
#include <bitset>
#include <assert.h>
#include <cstdlib>
#include <cmath>
#include <queue>
 
using namespace std;
 
typedef long long ll;
 
const int INF = 1e9, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
const int N = 1e6;

int d[4][301][301][301];

int Rec (int a1, int a2, int a3, int st) {
	if (d[st][a1][a2][a3] != -1) return d[st][a1][a2][a3];

	if (st == 2) return 1;
	if (!a1 && !a2 && !a3) return 0;

	int ans = 0;
	if (a1) ans = max (1 - Rec (a1 - 1, a2, a3, (st + 1) % 4), ans);
	if (a2) ans = max (1 - Rec (a1, a2 - 1, a3, (st + 2) % 4), ans);
	if (a3) ans = max (1 - Rec (a1, a2, a3 - 1, (st + 3) % 4), ans);

	return d[st][a1][a2][a3] = ans;
}

int main () {
	int t, n;
	cin >> t;

	while (t--) {
		cin >> n;

		int cnt[4] = {0, 0, 0, 0};
		memset (d, -1, sizeof (d));

		for (int i = 0; i < n; i++) {
			int a;
			cin >> a;
			cnt[a % 4]++;
		}

		int ans = Rec (cnt[1], cnt[2], cnt[3], 0);

		if (ans ^ (cnt[0] % 2)) cout << "Ghayeeth\n";
		else cout << "Siroj\n";
	}
}
