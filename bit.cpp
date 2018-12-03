#include<iostream>
#include<cstdio>
#include<ctime>
using namespace std;

const int MAXN = 100;

inline int lowbit(int x) {
	return x & (-x);
} 

int N;

int backTracking(int n, int left, int down, int right) {
	if (n >= N) {
		return 1;
	}
	int ret = 0;
	int avail = ((1 << N) - 1) & ~(left | down | right);
	for (int as = avail, a = lowbit(as); a; as ^= a, a = lowbit(as)) {
		ret += backTracking(n + 1, (left | a) << 1, down | a, (right | a) >> 1);
	}
	return ret;
}

int queens(int n) {
	N = n;
	return backTracking(0, 0, 0, 0);
}

int main() {
	int n;	
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		auto start = clock();
		int ret = queens(i);
		auto end = clock();
		cout << double(end - start) / CLOCKS_PER_SEC << endl; 
	}
	return 0;
}
