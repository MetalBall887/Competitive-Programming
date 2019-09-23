#include "vision.h"
#include <iostream>
//Let's look at some black point in the grid. If we color all cells that have distance from our point equal to K red, we'll
//get a diagonal square. So we need to check whether there is a square with side K where one black cell is the center and 
//the other one lies on the border. We mark diagonals that contain black cells as black. We have to find black diagonals
//with distance = K. Then we have to find also black antidiagonals with distance <= K. We can find the latter by defining
//if any antidiagonal has in segment [i-K;i)U(i;i+K] black diagonals. If not successful, swap diagonals and antidiagonals and
//try once more.

using namespace std;

int a[100000], k, t, H, W, K;

struct data {

	struct segment {
	int l, r;
	} prim, weak, sec;

	int prim_res, sec_res, zero, shortcut, l, r;
} diag, antid;

vector <int> tie (int a, int b)
{
	vector <int> c;

	c.push_back (a);
	c.push_back (b);

	return c;
}

void process (data& diag, bool rev, int H, int W, int K) {
	vector <int> v;

	diag.l = t;

	for (int i = (rev ? 0 : -H + 1); i < (rev ? W + H - 1 : W); i++) {
		v.clear ();
		for (int j = 0; j < H; j++) {
			int ji = (rev ? i - j : j + i);
			if (0 <= ji && ji < W) {
				v.push_back (j * W + ji);
			}
		}

		t++;
		add_xor (v);
	}

	diag.r = t;
	diag.prim.l = t;
	for (int i = diag.l; i < diag.r; i++) {
		if (i - K >= diag.l) {
			add_and (tie (i - K, i));
			t++;
		}
	}

	diag.prim.r = t;
	v.clear ();
	for (int i = diag.l; i < diag.r; i++) {
		v.push_back (i);
	}

	diag.shortcut = t + 1;
	add_or (v);
	add_not (t);
	t += 2;

	diag.zero = t;
	add_xor (tie (0, 0));
	t++;

	diag.weak.l = t;
	for (int i = diag.l; i < diag.r; i++) {
		v.clear ();
		for (int j = max (diag.l, i - K); j < min (diag.r, i + K + 1); j++) {
			if (j != i) v.push_back (j);
			else v.push_back (diag.zero);
		}
		add_or (v);
		t++;
	}
	diag.weak.r = t;

	diag.sec.l = t;
	for (int i = 0; i < diag.r - diag.l; i++) {
		add_and (tie (diag.l + i, diag.weak.l + i));
		t++;
	}
	diag.sec.r = t;

	v.clear ();
	diag.prim_res = t;
	for (int i = diag.prim.l; i < diag.prim.r; i++) {
		v.push_back (i);
	}
	add_or (v);
	t++;

	v.clear ();
	diag.sec_res = t;
	for (int i = diag.sec.l; i < diag.sec.r; i++) {
		v.push_back (i);
	}
	v.push_back (diag.shortcut);
	add_or (v);
	t++;

}

void construct_network (int H, int W, int K) {
	t = H * W;

	process (diag, false, H, W, K);
	process (antid, true, H, W, K);

	add_and (tie (diag.prim_res, antid.sec_res));
	int primsec = t;
	t++;

	add_and (tie (antid.prim_res, diag.sec_res));
	int secprim = t;
	t++;

	add_or (tie (primsec, secprim));
	t++;
}
