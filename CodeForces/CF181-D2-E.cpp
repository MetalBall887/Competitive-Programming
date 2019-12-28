#include <bits/stdc++.h>
//the idea is, when chips are too far away from each other, you can assign two parallel lines between them, which
//will succesfully divide chips if after moving one of the chips you'll put glue on a closest of cells on a line
//corresponding to the chip. There should be at least 4 cells of empty space between chips in any of the axis to
//separate them like that. That means, the first player has chances only if both chips are inside one 5x5 square
//that leaves us with, on the first sight, a lot of possibilities, but actually we should 
//1) consider only relative distance between chips (16 cases)
//2) eliminate symmetric cases (9 cases left)
//3) eliminate cases where they lie on one line as automatically winning (only 5 cases to consider)
//5 cases is possible to solve without computer
 
typedef long long ll;
 
const ll N = 1e6;
 
using namespace std;
 
 
 
int main () {
	int n, m, x1, y1, x2, y2;
	cin >> n >> m >> x1 >> y1 >> x2 >> y2;
 
	if (abs (x1 - x2) > 4 || abs (y1 - y2) > 4 || abs (x1 - x2) + abs (y1 - y2) >= 7) {
		cout << "Second";
	} else {
		cout << "First";
}
 
 
