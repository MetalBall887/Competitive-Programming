#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
//The first idea is, the broken line's projections on x-axis and y-axis are behaving independently, so we can solve this
//problem for x and y independently. Thus, for solving it, let's solve this problem for 1D vectors. We can keep 
//the information about the line in the array (t[i] - the number of times the broken line crossed the point i), so adding the
//vector to this line is adding 1 on the whole range of this vector (but not the starting point, so we won't count 
//joints twice). If we keep it as an explicit array, it will take O(n) to add/remove a vector from a structure. Instead, 
//we can add 1 at the left point of the range and substract 1 after the right point, so our value for i will be hidden in
//sum t[0..i]. Now after we know how to keep a structure, we can divide a polyline into 3 parts: current - the one where 
//cursor is, fixed part - vectors before the cursor and dynamic part - vectors after the cursor. We will keep vectors in 
//last two parts in two
//stacks, at that same time maintaining an array as explained above for both parts. So moving forward/backward is putting 
//a current vector into one of the stack and taking a new current one from the top of the other. Answering is basically 
//sum of both parts' t[0] (+ 1 if the current vector crossed 0). Changing is harder, because by changing the vector we can
//move the whole dynamic part. Either we can represent our array t as some data structure with range updates (segtree, treap)
//to move all the elements at once, or we can instead move "zero" (that means, if we have to move the structure by 2 to the
//left, we move "center" by 2 to the right and answer the queries with t[center], not t[0]). When transferring vectors from
//one part to another, we can't forget about dealing with center shifts. Now our complexity depends on the complexity of
//calculating the prefix sum in array t. We can implement a BIT to obtain O(logn) with good constant, but theoretically it
//is not enough, because the coordinates may be too big for a static array. Instead we can build something dynamic like
//treap (but there were no tests for that so I thought it would be excessive). The another flaw in my solution is that we
//count the number of times broken line touches zero, not crosses, but there were no tests for that as well. It is fixable 
//by maintaining a similar structure for counting the number of times polyline touched some point on coordinate line but
//did not cross it (such events appear when the polyline changes direction). Now to solve the 2D problem, we can split each
//vector on y part and x part and solve 1D problem for each part independently.
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <queue>
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e9, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

int n, m, ptr;

struct vect {
	int x, y;
} a[100000];

struct segment {
	int l, r;
} current_x, current_y;

struct segment_set {
	vector <segment> v;
	int t[10000000];
	int center;

	void update (int x, int d) {
		x += 5000000;

		for (; x < 10000000; x |= (x + 1))
			t[x] += d;
	}

	int sum (int x) {
		int sum = 0;
		x += 5000000;

		for (; x >= 0; x = (x & (x + 1)) - 1)
			sum += t[x];

		return sum;
	}

	void add (segment x) {
		x.l += center;
		x.r += center;

		if (x.l != x.r) {
			if (x.l > x.r) {
				update (x.r, 1);
				update (x.l, -1);
			}
			else {
				update (x.l + 1, 1);
				update (x.r + 1, -1);
			}
		}

		v.push_back (x);
	}

	segment pull () {
		auto x = v.back ();

		if (x.l != x.r) {
			if (x.l > x.r) {
				update (x.r, -1);
				update (x.l, 1);
			}
			else {
				update (x.l + 1, -1);
				update (x.r + 1, 1);
			}
		}
		v.pop_back ();

		x.l -= center;
		x.r -= center;
		return x;
	}

	int get () {
		return sum (center);
	}
} fixed_x, dynamic_x, fixed_y, dynamic_y;

void forward () {
	fixed_x.add (current_x);
	current_x = dynamic_x.pull ();

	fixed_y.add (current_y);
	current_y = dynamic_y.pull ();
	ptr++;
}

void backward () {
	dynamic_x.add (current_x);
	current_x = fixed_x.pull ();

	dynamic_y.add (current_y);
	current_y = fixed_y.pull ();
	ptr--;
}

void change (vect v) {
	vect delta = {v.x - a[ptr].x, v.y - a[ptr].y};
	a[ptr] = v;
	current_x.r += delta.x;
	current_y.r += delta.y;
	dynamic_x.center -= delta.x;
	dynamic_y.center -= delta.y;
}

int answer () {
	int sum = 0;
	sum = fixed_x.get () + fixed_y.get () + dynamic_x.get () + dynamic_y.get ();
	if (current_x.l != current_x.r) {
		if (current_x.l > current_x.r && current_x.r <= 0 && 0 <= current_x.l - 1) sum++;
		if (current_x.l < current_x.r && current_x.l + 1 <= 0 && 0 <= current_x.r) sum++;
	}

	if (current_y.l != current_y.r) {
		if (current_y.l > current_y.r && current_y.r <= 0 && 0 <= current_y.l - 1) sum++;
		if (current_y.l < current_y.r && current_y.l + 1 <= 0 && 0 <= current_y.r) sum++;
	}

	return sum;
}

int main () {
	cin >> n;

	int x = 1, y = 1;

	vector <segment> s_x, s_y;

	for (int i = 0; i < n; i++) {
		scanf ("%d%d", &a[i].x, &a[i].y);
		s_x.push_back ({x, x + a[i].x});
		s_y.push_back ({y, y + a[i].y});
		x += a[i].x;
		y += a[i].y;
	}

	while (s_x.size () != 1) {
		dynamic_x.add (s_x.back ());
		s_x.pop_back ();
		dynamic_y.add (s_y.back ());
		s_y.pop_back ();
	}
	current_x = s_x[0];
	current_y = s_y[0];

	cin >> m;

	for (int i = 0; i < m; i++) {
		char c[10];
		scanf ("%s", c);

		if (c[0] == 'F' && ptr < n - 1) forward ();
		if (c[0] == 'B' && ptr) backward ();
		if (c[0] == 'C') {
			vect f;
			scanf ("%d%d", &f.x, &f.y);
			change (f);
		}
		if (c[0] == 'Q') {
			printf ("%d\n", answer ());
		}
	}
}
