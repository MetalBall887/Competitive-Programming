//We were already given a working greedy algorithm, with which we can judge when to put which colors back. We only need one small optimization: once we decide
//which paint to put back it's equally optimal to put back any of paints as long as it will be put back before it's requested next time. This means that whenever
//a paint is requested next time it's needed it will either be optimal for the paint to stay on the scaffold or it will be put back and brought back again. If it's
//first, don't touch it until it's needed again, if it's second, it's "useless" and can be put back anytime even if by the given greedy algorithm it should have
//been another one. First we decide a scenario for paints 0...K-1 which are already on a scaffold and then after each request, which brings us to a solution
//that uses O(N+K) bits.

void ComputeAdvice(int *C, int N, int K, int M) {
	vector<vector<int>> last(N);
	vector<int> ans(N), ans_k(K);
	vector<int> request(N, -1);
	vector<int> ptr(N), st(N);
	set<pair<int, int>> s;
 
	for (int i = 0; i < N; i++) {
		last[C[i]].push_back(i);
	}
 
	for (int i = 0; i < N; i++) {
		last[i].push_back(N);
	}
 
	for (int i = 0; i < K; i++) {
		s.insert({last[i][0], i});
		st[i] = 1;
	}
 
	for (int i = 0; i < N; i++) {
		/*for (auto a : s) {
			cout << a.first << ' ' << a.second << endl;
		}
		cout << "----\n";*/
 
		request[C[i]] = i;
		if (!st[C[i]]) {
			int x = s.rbegin()->second;
			s.erase({last[x][ptr[x]], x});
			st[x] = 0;
			if (request[x] != -1) ans[request[x]] = 1;
			else ans_k[x] = 1;
			while(last[C[i]][ptr[C[i]]] <= i) ptr[C[i]]++;
			s.insert({last[C[i]][ptr[C[i]]], C[i]});
		} else {
			s.erase({last[C[i]][ptr[C[i]]], C[i]});
			while(last[C[i]][ptr[C[i]]] <= i) ptr[C[i]]++;
			s.insert({last[C[i]][ptr[C[i]]], C[i]});
		}
		st[C[i]] = 1;
	}
 
	for (int i = 0; i < K; i++) {
		WriteAdvice(ans_k[i]);
	}
 
	for (int i = 0; i < N; i++) {
		WriteAdvice(ans[i]);
	}
}

void Assist(unsigned char *A, int N, int K, int R) {
	vector<int> st(N);
	vector<int> bottom_shelf;
	for (int i = 0; i < K; i++) {
		if (A[i]) bottom_shelf.push_back(i);
		st[i] = 1;
	}
 
	A += K;
 
	for (int i = 0; i < N; i++) {
		int x = GetRequest();
		if (!st[x]) {
			st[bottom_shelf.back()] = 0;
			PutBack(bottom_shelf.back());
			bottom_shelf.pop_back();
		}
		st[x] = 1;
		if (A[i]) bottom_shelf.push_back(x);
	}
 
}
