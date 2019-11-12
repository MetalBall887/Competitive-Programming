#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <fstream>
//First, let's find when it's useful to use a magic stone. First, when your xor is 0. You use a stone, choose nim
//and pass your losing state to opponent. Second, when all piles have at most 1 element in it. You take the magic stone
//and choose the rules based on parity of piles left. In other cases, your state is winning for both nims and using a
//magic stone will give the winning state to your opponent. Intuition is, getting the first winning condition is hard, since
//it's up to your opponent to give you a state with xor 0 and he will try to avoid that and will have to do it, when there
//is no piles with weight > 1. The second condition looks more real. That means, the one who will get all piles 
//0 or 1, will win. So we ignore the last bit in binary representation of piles and play misere nim.
//But we also should be careful not to accidentally give our opponent a state with xor equal to 0 and at the same time we want
//to win misere, so we have to give states only with xor = 1 (including the last bit). That is possible by aconsidering n-th
//pile with one stone. Taking it means using the magic stone and changing the losing xor from 1 back to 0. In details, taking 
//this pile is optimal only when xor is 1 (or 0 without n-th pile), and we want to give our opponent state with xor only 
//equal to 0 (or 1 without n-th pile) which perfectly fits our rules, so the correctness of this winning strategy is implied
//by the correctness of nim winning strategy with our magic pile.
//The second phase (when the biggest pile has 1 stone) of misere nim is also influenced with the "ignored" last bit, 
//because one can pass his losing position and the other will have to respond with passing back, so it will depend on the number 
//of odd piles. 
#include <set>
#include <bitset>
#include <map>
#include <cstring>
#include <assert.h>
#include <cstdlib>
#include <cmath>
#include <queue>
 
#define N 1000000
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
class MagicNim {
public:
	string findWinner (vector <int> a) {
		int x = 0, pr = 0, mx = 0;

		for (int i : a) {
			x ^= i;
			pr ^= (i & 1);
			mx = max (mx, i);
		}

		//explicit winning states
		if (x == 0 || mx == 0) {
			return "Alice";
		}
		
		mx >>= 1;

		//first phase of misere, losing state (xor 0 if magic pile considered)
		if (mx >= 2 && x == 1) return "Bob";

		x >>= 1;
		
		cout << mx << ' ' << x << ' ' << pr << endl;

		//second phase of misere, losing state, have to consider the possible number of passes
		//for winning state we can choose the parity of the number of passes (by, deciding if we leave
		//1 or 0 after our first turn
		if (mx <= 1 && x == 1) {
			if (pr) return "Alice";
			else return "Bob";
		}

		return "Alice";
	}
};
