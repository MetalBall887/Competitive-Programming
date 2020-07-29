#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//Let's apply meet-in-the-middle approach. For both halves of cows find for every possible partition sum difference all sets that will have the partition that
//will have this difference of sums. Then, when matching both halves for each partition sum difference for the one half find the "complementing" one (their sum
//will be 0). Then for any subset from left half having this difference and right half having the complementing difference their union will have an equal partition
//This algorithm looks inefficient but in fact if we try to construct asymptotically worst scenario, it will be either 2^(n/2) or 0 subsets for each difference for
//each half (since it's better to "keep subsets together" to increase the complexity). If we want to use as much as we can, it will be (2/3)^(n/2) possible
//differences with 2^(n/2) subsets in it for the left part, the same for the right one. Now if we count the number of operations, each difference out of
//all (2/3)^(n/2) will have to match 2^(n/2)*2^(n/2)=2^n unions from both sides with overall complexity O((2/3)^(n/2)*2^n) = O(6^(n/2)).
 
using namespace __gnu_pbds;
 
#define N 2000003
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
int n, a[100], bn[N];
 
map < int, vector <int> > m_l, m_r;
 
int main () {
	cin >> n;
 
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
 
	int l = n / 2, r = n - l;
 
	int ter = 1;
 
	for (int i = 0; i < l; i++)
		ter *= 3;
 
	for (int i = 0; i < ter; i++) {
		
		int s = i, sum = 0;
 
		int bin = (1 << l) - 1;
 
		for (int j = 0; j < l; j++) {
			if (s % 3 == 0) bin -= (1 << j);
			if (s % 3 == 1) sum -= a[j];
			if (s % 3 == 2) sum += a[j]; 
			s /= 3;
		}
 
		m_l[sum].push_back (bin);
	}
 
	ter = 1;
 
	for (int i = 0; i < r; i++)
		ter *= 3;
 
	for (int i = 0; i < ter; i++) {
		
		int s = i, sum = 0;
 
		int bin = (1 << r) - 1;
 
		for (int j = 0; j < r; j++) {
			if (s % 3 == 0) bin -= (1 << j);
			if (s % 3 == 1) sum -= a[l + j];
			if (s % 3 == 2) sum += a[l + j]; 
			s /= 3;
		}
 
		m_r[sum].push_back (bin);
	}
 
	int ans = 0;
 
	for (auto a : m_l) {
		int x = a.first;
		auto& v1 = m_l[x];
		auto& v2 = m_r[x];
 
		for (int xl : v1)
			for (int xr : v2) {
				if (!bn[(xr << l) + xl]) {
					bn[(xr << l) + xl] = 1;
					ans++;
				}
			}
	}
 
	cout << ans - 1 << endl;
} 
