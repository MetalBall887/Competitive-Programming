#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//For the first subtask it's simple: wlog let |r| > |b| and r is on the left, connect r1 with b1, r2 with b2, etc. then you will have some unconnected red sockets, 
//you can connect them to the closest blue socket. Proof is simple: take any point p between rightmost red socket (r') and leftmost blue socket (b'), each socket
//should be in at least one connection with a socket of different color, this connection will go through p, so |ri - bi| = |ri - p| + |p - bi|, so the total distance
//is at least sum of distances of all sockets to p. Now choose p = b' and see that for the construction above the equation is strict.
//For the rest of the problem we should also notice that if there is a case of time r1 b2 r2 b1 (for some pair of sockets of diff. colors there is another such 
//pair between) it's not optimal to link r1 with b1, so if we divide the the row of points into block of colors, only sockets from adjacent blocks will be linked
//together. We can use this and the solution to the first subtask. Let d[i] be answer to first i sockets, i and j have different colors and are in adjacent color
//blocks, d[i] = min(d[i], (sol of 1st subtask in i..j) + d[j-1]). To manage 1st subtask part well, consider two cases: |r| > |b| and another and put p = b' or r'
//accordingly, so that the computation of the left part of the subtask is independent on i and right part is independent on j.

using namespace __gnu_pbds;
 
 
using namespace std;
 
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
 
const int N = 2000001;
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
ll d[N];
 
void process(vector<ll>& fst, vector<ll>& snd, ll from) {
	if(fst.empty()) return;
 
	vector<ll> dleft(fst.size() + snd.size() + 1, INF);
	vector<ll> dright(fst.size() + snd.size() + 1, INF);
 
	from -= (ll)fst.size() + (ll)snd.size();
	
	ll dist = snd[0] - fst.back();
	ll sum_len = 0, sz = 0;
 
	for (ll i = fst.size(); i >= 0; i--) {
		ll last = (i + from ? d[i + from - 1] : 0);
 
		if (i != fst.size()) sum_len += fst.back() - fst[i];
 
		dleft[sz] = last + sum_len;
		dright[sz] = last + sum_len + sz * dist;
		sz++;
	}
 
	for (ll i = 1; i <= max(fst.size(), snd.size()); i++) {
		dleft[i] = min(dleft[i-1], dleft[i]);
	}
 
	for (ll i = max(fst.size(), snd.size()) - 1; i >= 0; i--) {
		dright[i] = min(dright[i+1], dright[i]);
	}
 
	sum_len = 0;
 
	from += (ll)fst.size();
	for (ll i = 0; i < snd.size(); i++) {
		sum_len += snd[i] - snd[0];
		d[i + from] = sum_len;
		d[i + from] += min(dright[i+1], dleft[i+1] + (i + 1) * dist);
	}
}
 
ll min_total_length(vector<int> r, vector<int> b) {
	auto pr = r.begin(), pb = b.begin();
 
	ll n = r.size() + b.size();
 
	fill(d, d + n, INF);
 
	struct point {
		ll x;
		char color;
 
		bool operator<(point b) {
			return x < b.x;
		}
	};
 
	vector<point> v;
	vector<ll> red, blue;
 
	for (ll a : r) {
		v.push_back({a, 'r'});
	}
 
	for (ll a : b) {
		v.push_back({a, 'b'});
	}
 
	sort(v.begin(), v.end());
 
	for (ll i = 0; i < n; i++) {
		if (i && v[i-1].color != v[i].color) {
			if (v[i].color == 'r') {
				process(red, blue, i);
				red.clear();
			}
			else {
				process(blue, red, i);
				blue.clear();
			}
		}
 
		if (v[i].color == 'r') red.push_back(v[i].x);
		else blue.push_back(v[i].x);
	}
 
	if(v.back().color == 'r') process(blue, red, n);
	else process(red, blue, n);
 
	return d[v.size() - 1];
}
