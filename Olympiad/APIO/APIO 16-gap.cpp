#include "gap.h"
#include <bits/stdc++.h>
//First find globally leftmost and rightmost element. The difference between them is the sum of all gaps, so by dividing by the number of gaps we obtain the 
//average gap = AVG. The maximal gap will be at least the average, so if we divide all vertices into blocks by intervals of length AVG, the maximal gap will not
//be inside of any of the blocks. That means, we can compare only the rightmost point of the block with the leftmost point of the next block. First query will cost
//N + 1, all other queries will touch all points except first and last ones, there will be N - 1 of them, so overall cost will be N + 1 + N - 2 + N - 1 = 3N - 2.
 
typedef long long ll;
typedef long double ld;
 
using namespace std;
 
ll findSmall(int N) {
 
	vector <ll> v (N);
	ll mn, mx;
 
	MinMax (1, 1e18, &mn, &mx);
 
	ll s = mn, e = mx;
 
	v[0] = s, v[N-1] = e;
 
	int l = 0, r = N - 1;
 
	while (l + 1 < r) {
		MinMax(v[l] + 1, v[r] - 1, &s, &e);
		v[++l] = s, v[--r] = e;
	}
 
	for (int i = 1; i < N; i++) {
		v[i-1] = v[i] - v[i-1];
	}
 
	return *max_element(v.begin(), v.end() - 1);
}
 
ll findGap(int T, int N) {
 
	if (T == 1) {
		return findSmall(N);
	}
 
	ll mn, mx;
 
	MinMax (1, 1e18, &mn, &mx);
 
	ll s = mn, e = mx;
 
	ld d = (ld) (mx - mn - 2) / N;
 
	ld l = mn + 1, r = mn + 1 + d;
	ll gap = 0, mx_old = mn, last_ir = s;
 
	for (int i = 0; i < N - 1; i++) {
		ll il = ceil (l - 1e-7) + (ceil (l - 1e-7) == last_ir), ir = floor (r + 1e-7);
		//cout << il << ' ' << ir << endl;
		if (il > ir) continue;
		last_ir = ir;
		MinMax(il, ir, &mn, &mx);
		//cout << ' ' << mn << ' ' << mx << endl;
		if (mn != -1) {
			gap = max (gap, mn - mx_old);
			mx_old = mx;
		}
		l += d, r += d;
	}
	
	ll il = ceil (l - 1e-7) + (ceil (l + 1e-7) == last_ir), ir = floor (r + 1e-7);
	//cout << il << ' ' << ir << endl;
 
	
	if (il <= ir) MinMax(il, ir, &mn, &mx);
	//cout << ' ' << mn << ' ' << mx << endl;
 
	if (mn != -1 && il <= ir) {
		gap = max (gap, mn - mx_old);
		mx_old = mx;
	}
 
	gap = max (gap, e - mx_old);
 
	return gap;
}
