#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
inline long long read() {
	long long num = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch>'9') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		num = (num << 3) + (num << 1) + (ch ^ 48);
		ch = getchar();
	}
	return num * f;
}
vector<int>Coin, sumCost;
int find(int l, int r, int v) {
	int basic = sumCost[l], res = 1;
	while (l <= r) {
		int m = l + r >> 1;
		if (sumCost[m] - basic <= v)res = m, l = m + 1;
		else r = m - 1;
	}
	return res;
}
void solve() {
	int K = read(), N = read();
	vector<int>(K + 1).swap(Coin);
	for (int i = 1; i <= K; i++) Coin[i] = read();
	vector<int>(N + 1).swap(sumCost);
	for (int i = 1; i <= N; i++) sumCost[i] = sumCost[i - 1] + read();
	vector<int>dp(1 << K);
	int ans = -1;
	for (int i = 0; i < (1 << K); i++) {
		for (int j = 1; j <= K; j++) {
			if ((i >> j - 1) & 1) continue;
			dp[i | (1 << j - 1)] = max(dp[i | (1 << j - 1)], find(dp[i], N, Coin[j]));
		}
		if (dp[i] == N) {
			int sum = 0;
			for (int j = 1; j <= K; j++) {
				if ((i >> j - 1) & 1) continue;
				sum += Coin[j];
			}
			ans = max(ans, sum);
		}
	}
	cout << ans;
}
int main()
{
	solve();
	return 0;
}