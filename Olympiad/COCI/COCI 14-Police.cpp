#include <bits/stdc++.h>
//Construct a graph where nodes are shelves and edges are books that should be moved to other shelves. Note that the number
//of edges to each node is equal to the number of edges going out of the node. That means, we can create an Eulerian cycle, 
//which almost gives us the optimal answer but if there is no vacant place in the component, we have to create one, which will
//cost us one operation. So the number of operations in each component is the number of books "out of order" (+1). The book is
//out of order if we have to lift it. Of course, this characteristic depends on our sequence of moves so let's minimize the 
//number of such books in each shelf. If it has to be in another shelf, we can't do anything, so what we can do inside of the
//shelf is to sort the sequence in the least possible number of replacements. It is done by sorting with having a largest
//increasing subseqence as a "measure point", because then it will take us m - |lis| operations. And the minimal number of
//operations in the component is such sum of out-of-order books in each shelf + 1 if there is no free place to start from.
#define N 2000003
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

vector <int> a[1000], b[1000];
int x[N], y[N], n, m, z[1000], zr, lis[1000];
int d[1002], p[1000], ans, s[1000];

int find (int x) {
	if (p[x] == x) return x;
	return p[x] = find (p[x]);
}

void unite (int a, int b) {
	a = find (a), b = find (b);
	if (a == b) return;

	p[b] = a;
}

int main () {
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		p[i] = i;
		a[i].resize (m);
		for (int j = 0; j < m; j++) {
			cin >> a[i][j];
			x[a[i][j]] = i, y[a[i][j]] = j;
			if (!a[i][j]) z[i]++;
			zr += z[i];
		}
	}

	for (int i = 0; i < n; i++) {
		b[i].resize (m);
		for (int j = 0; j < m; j++) {
			int t;
			cin >> t;
			b[i][j] = ((x[t] != i || !t) ? -1 : y[t]);
			if (x[t] != i && t) {
				unite (x[t], i);
			}
		}
	}



	if (!zr) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (b[i][j] != j) {
					cout << -1;
					return 0;
				}
			}
		}
		cout << 0;
		return 0;	
	}

	for (int i = 0; i < n; i++) {
		fill (d, d + m + 1, N);
		d[0] = -1;

		for (int j = 0; j < m; j++) {
			if (b[i][j] == -1) continue;
			int l = 0, r = m;
			while (l < r) {
				int mid = (l + r + 1) / 2;
				if (d[mid] <= b[i][j]) l = mid;
				else r = mid - 1;
			}

			d[l + 1] = b[i][j];
		}

		for (int j = 0; j <= m + 1; j++) {
			if (d[j] == N) {
				s[i] = m - z[i] - j + 1;
				break;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		if (find (i) != i) {
			z[find (i)] |= z[i];
			s[find (i)] += s[i];
		}
	}

	for (int i = 0; i < n; i++) {
		if (find (i) == i) {
			if (!s[i]) continue;
			ans += s[i];
			if (!z[i]) ans++;
		}
	}

	cout << ans;
}
