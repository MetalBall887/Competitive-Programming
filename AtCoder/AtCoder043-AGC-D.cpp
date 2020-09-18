#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//There are some observations needed to be done. First of all, there won't be many reverses in this permutation. if i < j, a[i] > a[j] then a[i] and a[j] are
//from the same queue, so the LDS is at most 3. Also if any queue if A[i] > A[i+1], then when A[i] becomes minimum and get pulled from the queue, A[i+1]
//immediately becomes minimum after, so in the permutation they will go after each other. 
//Since the size of each queue is 3, there aren't many possible orderings:
//1) 3-2-1, 3-1-2: A[0], A[1], A[2] will be consequent in the permutation, consider them a block of size 3
//2) 2-1-3: A[0], A[1] will be consequent in the permutation, consider them a block of size 2, A[2] is a block of size 1
//3) 2-3-1, 1-3-2: A[1], A[2] will be consequent in the permutation, consider them a block of size 2, A[0] is a block of size 1
//4) 1-2-3: All numbers can be separated in the permutation, all blocks are of size 1 
//After we divide all queues in such blocks, permutation will be the sequence of these blocks sorted by the first elements. In the same way each permutation can be
//divided in such blocks: for each position from 1 to n if the current number is the maximum on this prefix, start a new block, otherwise add to the current one.
//Now to be able to form queues from these blocks reversely, we need each block to be of size at most 3 and the number of blocks of size 2 be at most the number of
//blocks of size 1. After this we can translate the sequence back to queues, we can merge one 1-block and 2-block in any of three ways explained above depending
//on the relation. So now we use dp d[i][j] - the number of permutations of size i, such that each block is of size at most 3 and the # of 2-blocks minus 
//# of 1-blocks is j. Be careful that j might be negative.

//using namespace __gnu_pbds;
 
#define N 2000001
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
ll d[10001][10005], n, P, offset = 3000;
 
int main () {
	cin >> n >> P;
 
	d[0][offset] = 1;
	d[1][offset + 1] = 1;
 
	for (int i = 2; i <= 3 * n; i++)
		for (int j = - i / 2; j <= i; j++) {
			d[i][offset + j] += d[i-1][offset + j - 1];
			if (d[i][offset + j] >= P) d[i][offset + j] -= P;
			d[i][offset + j] += d[i-2][offset + j + 1] * (i - 1) % P;
			if (d[i][offset + j] >= P) d[i][offset + j] -= P;
			if (i > 2) d[i][offset + j] += d[i-3][offset + j] * (i - 1) * (i - 2) % P;
		}
 
	ll ans = 0;
 
	for (int i = 0; i <= 3 * n; i++) {
		ans += d[3 * n][offset + i];
		if (ans >= P) ans -= P;
	}
 
	cout << ans;
}
