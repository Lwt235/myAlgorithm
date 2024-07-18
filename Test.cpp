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
	
}
int main()
{
	solve();
	return 0;
}