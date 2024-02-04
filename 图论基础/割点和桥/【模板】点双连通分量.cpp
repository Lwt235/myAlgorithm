#include <cstdio>
#include <iostream>
#include <vector>
#include <stack>
using namespace std;
vector<vector<int>>Edge;
vector<int>DFN, Low, Father;
stack<int>St;
vector<vector<int>>ans(1);
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
	St.push(x);
	DFN[x] = Time; Low[x] = Time;
	Time++;
	int child = 0, p;
	for (int i = 0; i < Edge[x].size(); i++)
	{
		int To = Edge[x][i];
		if (!DFN[To])
		{
			Father[To] = x; child++;
			Tarjan(To);
			Low[x] = min(Low[x], Low[To]);
			if (DFN[x] <= Low[To])
			{
				ans.push_back({});
				do {
					p = St.top(); St.pop();
					ans[col].push_back(p);
				} while (p != To);
				ans[col].push_back(x);
				col++;
			}
		}
		else if (To != Father[x])
			Low[x] = min(Low[x], DFN[To]);
	}
	if (Father[x] == -1 && child == 0)
	{
		ans.push_back({});
		ans[col++].push_back(x);
	}
}

int main()
{
	n = read(), m = read();
	vector<vector<int>>(n + 1).swap(Edge);
	vector<int>(n + 1).swap(DFN); vector<int>(n + 1).swap(Low); vector<int>(n + 1, -1).swap(Father);
	int i, j;
	for (int k = 0; k < m; k++)
	{
		i = read(); j = read();
		Edge[i].push_back(j);
		Edge[j].push_back(i);
	}
	for (int i = 1; i <= n; i++)
		if (!DFN[i]) Tarjan(i);

	cout << col - 1 << endl;
	for (int i = 1; i < col; i++)
	{
		cout << ans[i].size() << " ";
		for (int j = 0; j < ans[i].size(); j++)
			cout << ans[i][j] << " ";
		cout << endl;
	}
}