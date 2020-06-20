#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//Assume the number of elements in a sequence < x is R, d[k] is the number of subsegments with exactly k elements < x. 
//Also let p[k] be the number of prefixes with k elements < x and the same for s[x] but for suffices. 
//d[k] = sum i from 0 to R-k p[i]*s[(R-k)-i] as we have to remove some prefix and suffix and delete exactly R-k elements < x.
//d[R-k] = sum i from 0 to k p[i]*s[k-i]. Let p(x) = p[0]+p[1]x+p[2]x^2+... and s(x)=s[0]+s[1]x+s[2]x^2+...
//Note that f(x) = p(x)g(x) contains d[R-k] as k-th coefficient, so we need to compute p(x)g(x) through FFT. For k = R
//equation doesn't have to hold as a prefix and a suffix can overlap but for this case we can run a simple O(n) algo.
 
using namespace __gnu_pbds;
 
#define N 2000003
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef complex<ld> cd;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
int n, x;
 
void fft (vector <cd> & f, int inv) {
 
	if (f.size () == 1) return;
 
	int n = f.size ();
 
	vector <cd> f_even (n / 2), f_odd (n / 2);
 
 
	for (int i = 0; i < n / 2; i++) {
		f_even[i] = f[2 * i];
		f_odd[i] = f[2 * i + 1];
	}
 
	fft (f_even, inv);
	fft (f_odd, inv);
 
	ld ang = 2.0 * acos (-1) / n * inv;
 
	cd w (1);
 
	for (int i = 0; i < n / 2; i++) {
		f[i] = f_even[i] + w * f_odd[i];
		f[i + n / 2] = f_even[i] - w * f_odd[i];
 
		w *= cd (cos (ang), sin (ang));
	}
}
 
vector <cd> mult (vector <cd> a, vector <cd> b) {
	int bin = 1;
 
	while (bin <= a.size () + b.size ()) bin <<= 1;
	
	a.resize (bin);
	b.resize (bin);
 
	fft (a, 1);
	fft (b, 1);
 
	vector <cd> c = a;
 
	for (int i = 0; i < bin; i++) {
		c[i] *= b[i] / (ld) bin;
	}
 
	fft (c, -1);
 
	return c;
}
 
ll a[N];
 
vector<cd> p, s;
 
 
int main () {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> x;
 
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
 
	int k = 0;
 
	p.push_back (cd (1, 0));
	s.push_back (cd (1, 0));
 
	for (int i = 0; i < n; i++) {
		if (a[i] < x) {
			k++;
			p.push_back (cd ());
		}
		p[k] += 1.0;
	}
 
	k = 0;
 
	for (int i = 0; i < n; i++) {
		if (a[n - i - 1] < x) {
			k++;
			s.push_back (cd ());
		}
		s[k] += 1.0;
	}
 
	auto ans = mult (p, s);
 
	ll ans_0 = 0, last = -1;
 
	for (int i = 0; i < n; i++) {
		if (a[i] < x) last = i;
		ans_0 += i - last;
	}
 
	cout << ans_0 << ' ';
 
	for (int i = 1; i <= n; i++) {
		if (k < i) cout << 0 << ' ';
		else cout << (ll) round (real (ans[k - i])) << ' ';
	}
}
