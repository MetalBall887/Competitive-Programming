#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <fstream>
#include <map>
#include <unordered_map>
//The main idea is, retreat is absolutely useless. In a version with one string, it is trivial and the first player always
//wins. The key part of strategy is either ending an attack or giving a space for an opponent to attack and who ended his
//attack (made both pawns close to each other) for the last line, wins. If we retread we leave to out opponent a place for 
//"maneuvres". He can reduce the distance as he wants so the pool of possible moves is just increased, which is not optimal
//So only forward when possible. that means, we reduce the distance as we want and the first one to get 0 on every line, 
//loses. NOt to forget about the fact we can move 1..k pawns at once. This is the type of nim called Moore's extended nim.
//Also this problem has tricky cornercases.
#include <set>
#include <cstring>
#include <assert.h>
#include <cstdlib>
#include <cmath>
#include <queue>

#define N 1000000
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 1e9, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

int n, m, k;
vector <int> v;

bool can_make (string s, char c) {
	for (int i = 0; i < s.length (); i++) {
		if (s[i] == c) {
			if (i && s[i-1] == '-') return true;
			if (i <= s.length () - 2 && s[i+1] == '-') return true;
		}
	}

	return false;
}

int main () {
	cin >> n >> m >> k;
	k++;

	bool ok_r = false, ok_g = false;

	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;

		vector <int> cnt[500];
		for (int j = 0; j < s.length (); j++) {
			if (s[j] != '-') cnt[s[j]].push_back (j);
		}

		ok_r |= can_make (s, 'R');
		ok_g |= can_make (s, 'G');

		if (cnt['G'].size () == 1 && cnt['R'].size () == 1) {
			v.push_back (abs (cnt['R'][0] - cnt['G'][0]) - 1);
		}
	}

	if (!ok_g) {
		cout << "Second";
		return 0;
	} else if (!ok_r) {
		cout << "First";
		return 0;
	}

	vector <int> c (60);

	if (v.empty ()) {
		cout << "Draw";
		return 0;
	}

	for (int i : v) {
		for (int j = 0; j < 10; j++)
			if (i & (1 << j)) c[j] = (c[j] + 1) % k;
	}

	for (int i : c) {
		if (i) {
			cout << "First";
			return 0;
		}
	}

	cout << "Second";
}
