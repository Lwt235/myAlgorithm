#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
vector<int>lg2;
inline int read()
{
	int x = 0, f = 1; char ch = getchar();
	while (ch < '0' || ch>'9') { if (ch == '-') f = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = x * 10 + ch - 48; ch = getchar(); }
	return x * f;
}
vector<vector<int>> build(const vector<int>& arr)
{
	int n = arr.size() - 1;
	vector<int>(n + 1).swap(lg2);
	lg2[1] = 0;
	for (int i = 2; i <= n; i++)
		lg2[i] = lg2[i >> 1] + 1;
	vector<vector<int>>ST(n + 1, vector<int>(lg2[n] + 1));
	for (int i = 1; i <= n; i++)
		ST[i][0] = arr[i];
	for (int j = 1; j <= lg2[n]; j++)
		for (int i = 1; i <= n - (1 << j) + 1; i++)
			ST[i][j] = max(ST[i][j - 1], ST[i + (1 << (j - 1))][j - 1]);
	return ST;
}
int search(int L, int R, vector<vector<int>>& ST)
{
	int Len = lg2[R - L + 1];
	return max(ST[L][Len], ST[R - (1 << Len) + 1][Len]);
}
int main()
{
	int N = read(), M = read();
	vector<int>Nums(N + 1);
	for (int i = 1; i <= N; i++)
		Nums[i] = read();
	vector<vector<int>>ST = build(Nums);
	int L, R;
	for (int i = 1; i <= M; i++)
	{
		L = read(); R = read();
		printf("%d\n", search(L, R, ST));
	}
}