#include<iostream> 
#include<ctime>
#include<cstdio>
using namespace std; 

const int MAXN = 50; 

int N; 
int avail[MAXN][MAXN];

void forward_checking(int n, int a) {
	for (int i = n; i < N; ++i) {
		avail[i][a] ++;
		if (a + i - n < N)
			avail[i][a + i - n] ++;
		if (a - i + n >= 0)
			avail[i][a - i + n] ++;
	}
}

void reset_forward_checking(int n, int a) {
	for (int i = n; i < N; ++i) {
		avail[i][a] --;
		if (a + i - n < N)
			avail[i][a + i - n] --;
		if (a - i + n >= 0)
			avail[i][a - i + n] --;
	}
}

int dfs_forward_checking(int n) {
	if (n >= N) {
		return 1;
	}
	int ret = 0;
	for (int i = 0; i < N; ++i) if (avail[n][i] == 0) {
		forward_checking(n, i);
		ret += dfs_forward_checking(n + 1);
		reset_forward_checking(n, i);
	}
	return ret;
}

int nQueens(int n) {
	N = n;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			avail[i][j] = 0;
	return dfs_forward_checking(0);
}

//=======================================================

int state[MAXN];

bool check(int n, int a) {
	for (int i = 0; i < n; ++i) {
		if (state[i] == a || 
			state[i] == a + n - i || 
			state[i] == a - n + i)
			return false;
	}
	return true;
}

int dfs_backtracking(int n) {
	if (n >= N) {
		return 1;
	}
	int ret = 0;
	for (int i = 0; i < N; ++i) if (check(n, i)) {
		state[n] = i;
		ret += dfs_backtracking(n + 1);
	}
	return ret;
}


int nQueens2(int n) {
	N = n;
	return dfs_backtracking(0);
}



int main() {
	freopen("nQueens.txt", "w", stdout);

	int n;
	// cout << "Please input n: ";
	cin >> n;

	for (int i = 1; i <= n; ++i) {
		auto start = clock();
		int ans = nQueens(i);
		auto end = clock();
	
		// cout << i << " " << ans << endl;
		cout << double(end - start) / CLOCKS_PER_SEC << " ";

		start = clock();
		ans = nQueens2(i);
		end = clock();
	
		// cout << i << " " << ans << endl;
		cout << double(end - start) / CLOCKS_PER_SEC << endl;
	}
	
	return 0;
}
