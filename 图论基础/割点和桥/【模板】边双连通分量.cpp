#include <cstdio>
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct edge {
	int to;
	bool isBridge;
	edge() :isBridge(false) {};
	edge(int to, bool isBridge) :to(to), isBridge(isBridge) {};
};

vector<vector<edge>>Edge;
vector<int>DFN, Low, Father;
vector<vector<int>>ans(1);
vector<bool>vis;
int n, m, col = 1, Time = 1, tot = 0;

int read()
{
	int x = 0;
	char c = getchar();
	while (c < '0' || c > '9')
		c = getchar();
	while (c >= '0' && c <= '9')
	{
		x = (x << 1) + (x << 3) + (c ^ 48);
		c = getchar();
	}
	return x;
}

void Tarjan(int x)
{
	DFN[x] = Time; Low[x] = Time;
	Time++;
	int child = 0, p;
	for (int i = 0; i < Edge[x].size(); i++)
	{
		int To = Edge[x][i].to;
		if (!DFN[To])
		{
			Father[To] = x; child++;
			Tarjan(To);
			Low[x] = min(Low[x], Low[To]);
			if (Low[To] > DFN[x])
			{
				Edge[x][i].isBridge = true;
				for (int j = 0; j < Edge[To].size(); j++)
					if (Edge[To][j].to == x)
					{
						Edge[To][j].isBridge = true;
						break;
					}
			}
		}
		else if (To != Father[x])
			Low[x] = min(Low[x], DFN[To]);
	}
}

void solve(int x)
{
	ans[col].push_back(x); vis[x] = true;
	for (int i = 0; i < Edge[x].size(); i++)
	{
		int To = Edge[x][i].to;
		if (vis[To] || Edge[x][i].isBridge)
			continue;
		solve(To);
	}
}

int main()
{
	n = read(), m = read();
	vector<vector<edge>>(n + 1).swap(Edge);
	vector<int>(n + 1).swap(DFN); vector<int>(n + 1).swap(Low); vector<int>(n + 1, -1).swap(Father);
	int i, j;
	for (int k = 0; k < m; k++)
	{
		i = read(); j = read();
		Edge[i].push_back(edge(j, false));
		Edge[j].push_back(edge(i, false));
	}
	for (int i = 1; i <= n; i++)
		if (!DFN[i]) Tarjan(i);

	vector<bool>(n + 1, false).swap(vis);
	for (int i = 1; i <= n; i++)
		if (!vis[i])
		{
			ans.push_back({});
			solve(i);
			col++;
		}

	cout << col - 1 << endl;
	for (int i = 1; i < col; i++)
	{
		cout << ans[i].size() << " ";
		for (int j = 0; j < ans[i].size(); j++)
			cout << ans[i][j] << " ";
		cout << endl;
	}
}