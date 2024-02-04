#include <iostream>
#include <queue>
using namespace std;

vector<vector<int>>dp, Edge;
vector<int>Val;
int n, m;
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

void dfs(int x, int father)
{
	for (int i = 0; i < Edge[x].size(); i++)
	{
		int to = Edge[x][i];
		if (to != father)
		{
			for (int j = m + 1; j >= 1; j--)
				dp[to][j] = dp[x][j] + Val[to];
			dfs(to, x);
			for (int j = m + 1; j >= 1; j--)
				dp[x][j] = max(dp[x][j], dp[to][j - 1]);
		}
	}
}

int main()
{
	n = read(), m = read();
	vector<vector<int>>(n + 1).swap(Edge);
	vector<vector<int>>(n + 1, vector<int>(m + 2)).swap(dp);
	vector<int>(n + 1).swap(Val);
	int u, v, w;
	for (int i = 1; i <= n; i++)
	{
		v = read(), w = read();
		Edge[v].emplace_back(i);
		Val[i] = w;
	}
	dfs(0, -1);
	printf("%d", max(0, dp[0][m + 1]));
	return 0;
}