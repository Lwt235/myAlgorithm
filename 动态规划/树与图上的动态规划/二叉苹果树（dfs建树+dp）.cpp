#include <iostream>
#include <queue>
using namespace std;
struct node {
	int leftSon;
	int rightSon;
	int leftApple;
	int rightApple;
	node(int leftSon = -1, int rightSon = -1, int leftApple = -1, int rightApple = -1) :leftSon(leftSon), rightSon(rightSon), leftApple(leftApple), rightApple(rightApple) {};
};

struct edge {
	int to;
	int weight;
	edge(int to = -1, int weight = -1) :to(to), weight(weight) {};
};

vector<vector<int>>dp;
vector<vector<edge>>Edge;
vector<node>Tree;
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

void build(int x, int father)
{
	int g = 0;
	for (int i = 0; i < Edge[x].size(); i++)
	{
		int To = Edge[x][i].to;
		if (To != father)
		{
			g++;
			if (g == 1)
			{
				Tree[x].leftSon = To;
				Tree[x].leftApple = Edge[x][i].weight;
			}
			else
			{
				Tree[x].rightSon = To;
				Tree[x].rightApple = Edge[x][i].weight;
			}
			build(To, x);
		}
	}
}

int dfs(int x, int branch)
{
	if (Tree[x].leftSon == -1 && Tree[x].rightSon == -1)
		return 0;
	if (branch == 0)
		return 0;
	if (dp[x][branch] != 0)
		return dp[x][branch];
	for (int i = 0; i <= branch; i++)
	{
		if (i == 0)
			dp[x][branch] = max(dp[x][branch], dfs(Tree[x].rightSon, branch - 1) + Tree[x].rightApple);
		else if (i == branch)
			dp[x][branch] = max(dp[x][branch], dfs(Tree[x].leftSon, branch - 1) + Tree[x].leftApple);
		else
			dp[x][branch] = max(dp[x][branch], dfs(Tree[x].leftSon, i - 1) + Tree[x].leftApple + dfs(Tree[x].rightSon, branch - i - 1) + Tree[x].rightApple);
	}
	return dp[x][branch];
}

int main()
{
	int n = read(), m = read();
	vector<node>(n + 1).swap(Tree);
	vector<vector<edge>>(n + 1).swap(Edge);
	vector<vector<int>>(n + 1, vector<int>(m + 1)).swap(dp);
	int u, v, sumApple;
	for (int i = 1; i < n; i++)
	{
		u = read(), v = read(), sumApple = read();
		Edge[u].emplace_back(v, sumApple);
		Edge[v].emplace_back(u, sumApple);
	}
	build(1, 0);
	printf("%d", dfs(1, m));
	return 0;
}