#include <iostream>
#include <queue>
using namespace std;
vector<vector<int>>dp;
vector<int>indegree, father, r(1);
inline int read()
{
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9')
	{
		if (ch == '-')
			f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		x = (x << 3) + (x << 1) + (ch ^ 48);
		ch = getchar();
	}
	return f * x;
}
int topological_dp(int n)
{
	int ans = -0x7fffffff;
	queue<int>Qu;
	for (int i = 1; i <= n; i++)
	{
		if (indegree[i] == 0)
			Qu.emplace(i);
	}
	while (!Qu.empty())
	{
		int selected = Qu.front(); Qu.pop();
		dp[selected][1] += r[selected];
		ans = max(ans, max(dp[selected][0], dp[selected][1]));
		indegree[father[selected]]--;

		dp[father[selected]][0] += max(dp[selected][1], dp[selected][0]);
		dp[father[selected]][1] += max(dp[selected][0], 0);

		if (indegree[father[selected]] == 0)
			Qu.emplace(father[selected]);
	}
	return ans;
}
int main()
{
	int n = read();
	vector<int>(n + 1, 0).swap(indegree);
	vector<int>(n + 1, 0).swap(father);
	vector<vector<int>>(n + 1, vector<int>(2)).swap(dp);
	for (int i = 0; i < n; i++)
		r.emplace_back(read());

	int l, k;
	for (int i = 1; i < n; i++)
	{
		l = read(); k = read();
		father[l] = k;
		indegree[k]++;
	}

	printf("%d", topological_dp(n));

}