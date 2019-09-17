#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
//Main idea: we can greedily determine the moving algorithm of a second player: he will move to the side that is closer to him
//so we can view our segments as a pair of points. Everytime we can see whether he's going to mive to the left or to the
//right. We don't want him to move to the same side twice, since we could just remove the middle segment and the distance
//won't change. That means, we would want him to move in zig-zag way. Assume we already ordered our segments in an optimal way,
//then the answer will be l0 + (l0 - r1) + (l2 - r1) + ... + ln or -r0 + (l1 - r0) ... so after grouping it will look like
//2(l0 + l2 + l4 + l6 ... - r1 - r3 - r5 ...). We can greedily assign the order and don't worry about having both ends
//of one segment in the answer since li - ri <= 0.
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <queue>
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e9, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

int l[1000000], r[1000000], n;

int main () {

	cin >> n;

	for (int i = 0; i < n; i++)
		scanf ("%d%d", &l[i], &r[i]);

	sort (l, l + n + 1);
	sort (r, r + n + 1);
	reverse (l, l + n + 1);

	ll ans = 0, sum = 0;

	for (int i = 0; i <= n; i++) {
		sum += 2 * (l[i] - r[i]);
		ans = max (ans, sum);
	}

	cout << ans;
}
