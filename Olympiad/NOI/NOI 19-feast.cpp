#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//The idea is following:
//if you have consecutive positive or consecutive negative numbers, group them. Eliminate negative numbers on the sides as they won't improve the answer.
//Now our array looks like +-+-...-+-+ where + is positive number and - is negative number. It would be optimal to take all positive numbers if we could,
//but it can be that we will have more than k segments like that. Two things we can do: remove a positive segment and take a negative segment to join two
//positive ones together. Both operations cost negative amount, so we must pick them such way their total cost is minimized. In case of first we can see 
//that it makes sense only if this segment is not joined with another one and the same it doesn't make sense to add negative-cost segment to join segments 
//where one of them is removed. Thus, our problem now is tranferred to: on an array of numbers to choose some numbers such that their total cost is minimized 
//and no adjacent numbers are chosen. To do that, consider this greedy approach: take the smallest element and consider it and his both neighbors (denote - 
//as not chosen and x as chosen). In case of --- we can always pick the middle one (which is the global minimum thus in any answer with --- at this place we 
//can exchange any chosen number to the middle one and improve the answer), in case of x-- and --x we also can exchange to the middle one and improve the 
//answer. Thus, the only two possible assignments for these 3 consecutive elements are x-x and -x-. Now try to merge these three numbers into one, where -x- 
//state will be "not chosen" and x-x will be "chosen". Note that it behaves exactly like one number in terms of adjacency rules and also choosing this 
//"number" increases the number of chosen "numbers" by one and now from this triple at least one number is always chosen, so now we need to choose one 
//less number, so instead of k we need to solve the problem on k-1. Continue until k = 0.
 
using namespace __gnu_pbds;
 
using namespace std;
 
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
 
const ll N = 2000001;
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

ll l[N], r[N], p[N], sz[N], sum[N];
ll a[N], n, k, m;
ll ans;

set<pair<ll, int>> s;

int find(int x) {
	if (p[x] == x) return x;
	return p[x] = find(p[x]);
}

bool unite(int a, int b) {
	a = find(a), b = find(b);
	if (a == b) return false;

	if (sz[a] < sz[b]) swap(a, b);

	sz[a] += sz[b];
	p[b] = a;

	if (l[b] < l[a]) l[a] = l[b];
	if (r[a] < r[b]) r[a] = r[b];

	return true;
}

int main() {
	cin >> n >> k;

	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	vector<ll> v;

	v.push_back(a[0]);
	for (int i = 1; i < n; i++) {
		if ((v.back() >= 0) != (a[i] >= 0)) v.push_back(a[i]);
		else v.back() += a[i];
	}

	m = n;
	n = v.size();

	int L = 0, R = n - 1;

	if (v[0] < 0) L++;
	if (v.back() < 0) R--;

	if (L > R) {
		cout << 0;
		return 0;
	}

	int cnt = 0;

	for (int i = L; i <= R; i++) {
		if (v[i] >= 0) {
			ans += v[i];
			cnt++;
		}
		else v[i] = -v[i];

		l[i] = r[i] = p[i] = i;
		sum[i] = v[i], sz[i] = 1;

		s.insert({sum[i], i});
	}

	while (!s.empty() && cnt > k) {

		int x = s.begin()->second;
		s.erase(s.begin());

		if (x != find(x)) continue;

		if (l[x] - 1 < L) {
			int rx = find(r[x] + 1);
			ans -= sum[x];
			s.erase({sum[rx], rx});
			L = r[rx] + 1;
			cnt--;
			continue;
		}

		if (r[x] + 1 > R) {
			int lx = find(l[x] - 1);
			ans -= sum[x];
			s.erase({sum[lx], lx});
			R = l[lx] - 1;
			cnt--;
			continue;
		}

		if (l[x] - 1 >= L && r[x] + 1 <= R) {
			int lx = find(l[x] - 1), rx = find(r[x] + 1);

			s.erase({sum[lx], lx});
			s.erase({sum[rx], rx});
			unite(lx, x);
			unite(x, rx);
			ans -= sum[x];
			sum[x] = sum[lx] + sum[rx] - sum[x];
			sum[find(x)] = sum[x];
			x = find(x);
			s.insert({sum[x], x});
			cnt--;
		}
	}

	cout << ans;
}
