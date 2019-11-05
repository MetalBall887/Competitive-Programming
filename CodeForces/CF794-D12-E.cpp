#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
//Tackling the original problem may be very hard, so let's try some simplifying first. 
//First, let's not count first k turns. Second, let's first find out if our obtained
//number will be not lower than x, so all numbers will either be 0 if lower and 1 if not.
//Now, two ideas: 1) If a player "likes" the value in the middle of a current 
//segment, he can take numbers from the different side than the opponent and they will have to
//get to the middle. 2) If he doesn't like the middle, his opponent does, so he will reflect his turns too.
//Those rules above were pretty abstract, but they already gave an insight that the value will be
//determined by one of those players in first two turns, then the player in a winning position will succesfully
//keep it. More detailed, if n is even, first player can choose the best from two in the middle, take 
//the element from the opposite side and reflect every move. If the both are bad, they both are good
//for his opponent, so the first player can make every move and the second player will ensure his victory
//by reflecting moves. If n is odd, we can try both possible moves and solve even n from perspective of the
//second player but with one exception. If the actual middle value is 0, the second player will start reflecting
//from the first his turn and first player will have no choice.
//After we solved this subproblem we could do a binary search but it can be seen that the result mainly depends
//on middle values, so for even it will be maximum between two middle values and for odd n min (a[i/2], max (a[i/2-1], a[i/2+1])).
//Last part, k first turns is just choosing one optimal segment, what can be done in O(n) and for each "middle" we will find
//the minimal number of deletions we need to make this the middle.
#include <fstream>
#include <set>
#include <bitset>
#include <cstring>
#include <map>
#include <cassert>
#include <cstdlib>
#include <cmath>
#include <queue>
 
#define N 1000000
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e9, MOD = 1e9 + 7, MOD2 = 1e6 + 2;
 
int a[N], n, k, d[N];
 
int f (int l, int r) {
	if (r - l == 1) {
		return max (a[l], a[r]);
	} else {
		return min (a[l + 1], max (a[l], a[r]));	
	}
}
 
int main () {
	ios::sync_with_stdio (0);
	cin.tie (NULL);
 
	cin >> n;
 
	int ans = 0;
 
	for (int i = 0; i < n; i++)
		cin >> a[i];
 
	for (int i = 0; i < n - 1; i++) {
		int len = 2 * min (i, n - i - 2) + 2;
 
		d[n - len] = max (d[n - len], f (i, i + 1));
	}
 
	for (int i = 0; i < n - 2; i++) {
		int len = 2 * min (i, n - i - 3) + 3;
 
		d[n - len] = max (d[n - len], f (i, i + 2));
	}
 
	for (int i = 0; i < n; i++) {
		d[n-1] = max (d[n-1], a[i]);
	}
 
	for (int i = 2; i <= n; i++) {
		d[i] = max (d[i], d[i-2]);
	}
 
	for (int i = 0; i < n; i++) {
		cout << d[i] << ' ';
	}
}
