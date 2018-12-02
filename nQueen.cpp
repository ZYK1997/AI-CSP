#include<iostream>
#include<cstdio>
#include<ctime>
using namespace std;

const int MAXN = 50;

int N;
int state[MAXN];

//==========================================
//	forward checking
//	=======================================

int avail[MAXN][MAXN];

void forward_checking(int n, int a) {
	state[n] = a;
	for (int i = n; i < N; ++i) {
		avail[i][a] ++;
		if (a + i - n < N)
			avail[i][a + i - n] ++;
		if (a - i + n >= 0)
			avail[i][a - i + n] ++;
	}
}

void reset_forward_checking(int n, int a) {
	state[n] = -1;
	for (int i = n; i < N; ++i) {
		avail[i][a] --;
		if (a + i - n < N)
			avail[i][a + i - n] --;
		if (a - i + n >= 0)
			avail[i][a - i + n] --;
	}
}

bool dfs_forward_checking(int n) {
	if (n >= N) {
   /*      for (int i = 0; i < N; ++i) { */
		//     cout << state[i] << " ";
		// }	
		// cout << endl;
		
		return true;
	}
	for (int i = 0; i < N; ++i) if (avail[n][i] == 0) {
		forward_checking(n, i);
		if (dfs_forward_checking(n + 1))
			return true;
		reset_forward_checking(n, i);
	}
	return false;
}

void nQueen(int n) {
	N = n;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			avail[i][j] = 0;
	dfs_forward_checking(0);
}

//==============================================================================
// back tracking
//=============================================================================

bool check(int n, int a) {
	for (int i = 0; i < n; ++i) {
		if (state[i] == a || state[i] == a + n - i || state[i] == a - n + i)
			return false;
	}
	return true;
}

bool dfs_backtracking(int n) {
	if (n >= N) {
	   /*  for (int i = 0; i < N; ++i) { */
		//     cout << state[i] << " ";
		// }	
		// cout << endl;

		return true;
	}
	for (int i = 0; i < N; ++i) if (check(n, i)) {
		state[n] = i;
		if (dfs_backtracking(n + 1))
			return true;
		state[n] = -1;
	}
	return false;
}

void nQueen2(int n) {
	N = n;
	dfs_backtracking(0);
}

int main() {
	freopen("nQueen.txt", "w", stdout);

	int n;
	// cout << "Please input n = ";
	cin >> n;

	for (int i = 1; i <= n; ++i) {
		auto start = clock();
		nQueen(i);
		auto end = clock();
		cout << double(end - start) / CLOCKS_PER_SEC << " ";
		
		start = clock();
		nQueen2(i);
		end = clock();
		cout << double(end - start) / CLOCKS_PER_SEC << endl;
	}
	return 0;
}
