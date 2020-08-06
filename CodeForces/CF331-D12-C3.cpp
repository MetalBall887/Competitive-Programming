#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//Lemma: let a[x] be the answer for x. Show that a[x-1] <= a[x].
//By induction: let's say it works for all x 0 .. x-1. Then it would be optimal for x to subtract the largest digit (let it be k). Then a[x] = a[x-k] + 1.
//The same holds for x-1 and also if max digit for x is k, for x-1 it is either k, k-1 or 9. So let's say k' >= k-1. 
//Then a[x-1] = a[x-1-k']+1 <= a[x-1-(k-1)] + 1 = a[x-k] + 1 = a[x]. A consequence is, subtracting the maximal digit from the number is always optimal. 
//Let's split a number in upper, middle and lower 6 digits.
//Let d[x][n] be the number of subtractions for the number n to become <= 0 if the "dominating" digit is x (means if max. digit < x, x is subtracted) and
//p[x][n] - the number <= 0 that we will stop at. For n <= 1e6 answer is d[0][n], for example, for middle + lower digits we can skip lower digits iterations with
//this dp where dominating digit is max. middle digit. For upper + middle + lower digits we would want to do the same thing but the number of states in dp would be
//1e12. However, we don't need all these states because when we change the upper digits, (middle + lower) is guaranteed to become 999999...999x, so we need to
//precompute only ten different (middle + lower) variants (except the one we're starting with) and decrease the upper part in O(1) with this precomputation.

//using namespace __gnu_pbds;

#define N 1000003
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
const int M = 1e6;
 
int mxd[M + 1], d[10][M], p[10][M];
 
ll n;
 
pair <ll, int> cache[10][10];
 
pair <ll, int> count (ll x, int dm = 0) {
	int l = x / M, r = x % M;
	ll sm = 0, last;
 
	while (l >= 0) {
		sm += d[max (dm, mxd[l])][r];
		last = p[max (dm, mxd[l])][r];
		l--;
		r = M - last;
	}
 
	return {sm, last};
}
 
int main () {
	cin >> n;
 
	for (int i = 0; i <= M; i++) {
		mxd[i] = max (mxd[i / 10], i % 10);
	}
 
	for (int i = 1; i < 10; i++) {
		p[i][0] = i;
		d[i][0] = 1;
	}
 
	for (int i = 0; i < 10; i++) {
		for (int j = 1; j < M; j++) {
			if (j < i) {
				p[i][j] = i - j;
				d[i][j] = 1;
			} else {
				int k = max (mxd[j], i);
				d[i][j] = d[i][j - k] + 1;
				p[i][j] = p[i][j - k];
			}
		}
	}
 
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			cache[i][j] = count ((ll) M * M - j, i);
 
 
	ll l = n / ((ll) M * M), r = n % ((ll) M * M);
	ll sm = 0, last;
	pair <ll, int> a;
	
	a = count (r, mxd[l]);
	sm += a.first, last = a.second;
	l--;
 
	while (l >= 0) {
		sm += cache[mxd[l]][last].first;
		last = cache[mxd[l]][last].second;
		l--;
	}
 
	cout << sm;
}
