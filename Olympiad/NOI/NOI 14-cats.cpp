#include <bits/stdc++.h>
//Key statements:
//1. Since we insert 3 elements before additions in S2, it's no difference whether we remove those elements in S2 or not so
//last two commands do nothing
//2. Instead of flipping bits in stack all the time we can precalculate if the element we're pushing into S1 will have its bit
//swapped, which for x will depend on the number of S1 pops before popping x but after pushing x. It will do the sane for
//the parity of S1 pushes in this time period. It will always be odd for the first element and thus even for the second one
//because we push elements in S1 in pairs. After those consideration pseudocode will look like this:
//COUNTER = X                           We can see an implementation of iterative dfs here.
//WHILE COUNTER > 0
//  S2 PUSH T1
//  S1 POP                              After constructing a dfs tree of this program we may notice that it's always 
//  IF T2 > L                           the lowest multiply of 2N above with occasional +1. Now let's construct the same
//    COUNTER = COUNTER - 1             tree but for parities and observe that the right subtree is just a negation of
//    IF COUNTER == 0 PRINT T2          the left subtree. That means, that everytime you go right in this tree, you negate
//  ELSE                                your answer, which is originally 0. We can implement order statistic but also notice
//    ADD 2N TO T2                      that the sizes are always 2^i so this order statistic turns right when he sees 1
//    S1 PUSH (T2 XOR 1)                in an according bit. Also not to forget that everytime all nodes are visited S1 returns
//    S1 PUSH T2                        to its original state and starts over so we have to ignore such iterations
 
#define N 1000001
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
int q;
 
 
 
int main () {
	cin >> q;
 
	for (int i = 0; i < q; i++) {
		ll x, l, n;
		cin >> x >> l >> n;
 
		x--;
		if (l / (2 * n) + 2 <= 62) x %= (1LL << (l / (2 * n) + 2));
 
		cout << 2 * n * (l / (2 * n) + 1) + __builtin_popcountll (x) % 2 << '\n';
	}
}
