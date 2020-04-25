#include "snakelib.h"	
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//We can simultaneously find out both ends with precision loss up to K with binary search, just everytime we divide the 
//interval, we expect the snake to move by K. After we have small enough intervals, we can find all possible head/tail 
//positions and the smallest length and the biggestlength will differ by at most 2k+1, so from all lengths we can take a median
//We actually use like this too many questions, so to reduce the number we have to divide the first intervals not in 2 but 
//in 3 (since intervals will become different after that we will not be able to do that again).
 
using namespace __gnu_pbds;
 
#define N 2000003
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
int n, k, m = 1000, p, q;
int l, r;
 
int l1 = 0, r1 = 12121, l2 = 0, r2 = 12121;
 
/*void ask_snake (int mid1, int mid2, char* a, char* b) {
	if (l <= mid1 && mid1 <= r) *a = 's';
	else if (mid1 < l) *a = 'b';
	else *a = 'f';
 
	if (l <= mid2 && mid2 <= r) *b = 's';
	else if (mid2 < l) *b = 'b';
	else *b = 'f';
}
int get_speed () {
	return 0;
}
void tell_length (int x) {
	if (abs (r - l + 1 - x) <= k) cout << "fine!\n";
	else cout << l << ' ' << r << ' ' << k << ' ' << x << endl;
}*/
 
int main () {
	k = get_speed ();
	char a, b;
	int mid1 = 4041, mid2 = 8082;
	l1 = l2 = 0;
	r1 = r2 = 12121;
	l = rand () % 12122, r = l + rand () % (12122 - l - 1);
	ask_snake (mid1, mid2, &a, &b);
 
	if (a == 's') {
		r1 = mid1;
		if (b == 's') {
			l2 = mid2;
		} else {
			l2 = mid1, r2 = mid2 - 1;
		}
	} else if (a == 'b') {
		if (b == 'b') {
			l1 = l2 = mid2 + 1;
		} else if (b == 's') {
			l1 = mid1 + 1, r1 = mid2;
			l2 = mid2;
		} else {
			l1 = mid1 + 1, r1 = mid2 - 1;
			l2 = mid1 + 1, r2 = mid2 - 1;
		}
	} else {
		r1 = r2 = mid1 - 1;
	}
 
	for (int i = 0; i < 12; i++) {
		r1 += k;
		r2 += k;
		r2 = min (r2, 12121);
		r1 = min (r1, 12121);
		mid1 = (l1 + r1) / 2, mid2 = (l2 + r2 + 1) / 2;
		ask_snake (mid1, mid2, &a, &b);
	
		if (a == 'b') l1 = mid1 + 1;
		else if (a == 's') r1 = mid1;
		else r1 = mid1 - 1;
 
		if (b == 'b') l2 = mid2 + 1;
		else if (b == 's') l2 = mid2;
		else r2 = mid2 - 1;
	}
 
	vector <int> v;
 
	for (int i = l1; i <= r1; i++)
		for (int j = l2; j <= r2; j++) {
			if (i <= j) v.push_back (j - i + 1);
		}
 
	sort (v.begin(), v.end());
 
	v.erase (unique (v.begin(), v.end()), v.end ());
	tell_length ((v.back () + v[0]) / 2);
	
}
