#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <set>
//Let's call a range between two same numbers segments (for numbers i segment will be i-th)
//First we have to notice that if no segments lie inside another one, for each two segments we can process them in any order
//(converging a segment) and all orders will be optimal. For segments, one of them lie in another, it's better to first
//converge a smaller segment. The greedy idea is to always pick segments that have no other segments inside. If we call
//the number of segments inside rank, we can sort segments by their ranks and process in that order, because all segments
//inside segment a will have lower ranks than a-th rank so will be processed sooner. The hardest part is indices. We can 
//know them by explicitly constructing every swap operation, for example, on linked list. One hard part is, segment
//may converge not only after some another converging but in its process which pretty much makes the task more difficult.
//To deal with this case I use variable cur_deleted to remember how many segments were deleted during our converging
//and substract 2 from pos_l each time segment is deleted. We calculae first pos_l and pos_r by their original position
//minus all elements deleted before this operation. Until we start moving one of the elements, it's a correct way but
//then we lose track on the place where left element would be in original state of array.
#include <cstring>
#include <assert.h>
#include <cstdlib>
#include <cmath>
#include <queue>
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e9, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

int p[100001], n, l[50001], r[50001], sorted[100001];
int rnk[100001], u[50001], cur_deleted;

struct BIT {
	int t[100001];

	void update (int x, int d) {
		for (; x <= 2 * n; x = (x | (x + 1)))
			t[x] += d;
	}

	int get (int r) {
		int sum = 0;
		for (; r >= 0; r = (r & (r + 1)) - 1)
			sum += t[r];
		return sum;
	}

	int get (int l, int r) {
		return get (r) - get (l - 1);
	}
} del, pairs;

bool C (int i, int j) {
	return rnk[i] < rnk[j];
}

struct Node {
	int val, x;
	Node *prev, *next;

	Node (int val, int x) : val (val), x (x), prev (NULL), next (NULL) {}
};

Node* a[100000], *start;

void remove (Node* x, bool real) {

	if (real && !u[x -> val]) {
		cur_deleted += 2;
		del.update (l[x -> val], 1);
		del.update (r[x -> val], 1);
		u[x -> val] = 1;
	}

	if (!x -> prev && !x -> next) return;

	if (!x -> prev) {
		x -> next -> prev = NULL;
		start = x -> next;
		return;
	}

	if (!x -> next) {
		x -> prev -> next = NULL;
		return;
	}

	Node *l = x -> prev, *r = x -> next;

	l -> next = r;
	r -> prev = l;

	if (l -> val == r -> val) {
		remove (l, true);
		remove (r, true);
	}

}

Node* insert (Node* x, Node* l) {
	Node* m = new Node (x -> val, x -> x);

	if (!l -> next) {
		l -> next = m;
		return m;
	}


	auto r = l -> next;
	l -> next = m;
	m -> prev = l;

	r -> prev = m;
	m -> next = r;

	return m;
}

int main () {

	memset (l, -1, sizeof (l));
	cin >> n;

	for (int i = 0; i < 2 * n; i++) {
		scanf ("%d", &p[i]);
		a[i] = new Node (p[i], i);
		a[i] -> val = p[i];
		a[i] -> x = i;
		if (i) {
			a[i] -> prev = a[i-1];
			a[i-1] -> next = a[i];
		}
	}

	start = a[0];

	for (int i = 0; i < 2 * n; i++) {
		if (l[p[i]] == -1) l[p[i]] = i;
		else {
			r[p[i]] = i;
			rnk[p[i]] = pairs.get (l[p[i]], r[p[i]]);
			pairs.update (l[p[i]], 1);
		}
	}

	for (int i = 0; i < n; i++)
		sorted[i] = i + 1;

	vector <int> ans;

	sort (sorted, sorted + n, C);

	for (int i = 0; i < n; i++) {
		int x = sorted[i];
		if (u[x]) continue;

		auto p = a[l[x]];

		int pos_l = l[x] - del.get (0, l[x]);
		int pos_r = r[x] - del.get (0, r[x]);
		cur_deleted = 0;

		while (p -> next != a[r[x]]) {
			ans.push_back (pos_l - cur_deleted);
			auto t = insert (p, p -> next);

			remove (p, false);
			p = t;

			f = start;
			pos_l++;
		}

		remove (p, true);
		remove (a[r[x]], true);
	}

	cout << ans.size () << endl;

	for (int a : ans)
		printf ("%d\n", a + 1);
}
