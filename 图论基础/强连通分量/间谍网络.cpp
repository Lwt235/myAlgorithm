#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <unordered_set>
#include <unordered_map>
using namespace std;

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

void dfs(const vector<vector<int>>& Edge, vector<int>& DFN, vector<int>& val, vector<int>& Low, stack<int>& St, unordered_set<int>& map, int x, int& Time, vector<int>& color, int& col, vector<int>& colorVal, vector<int>& root)
{
	St.push(x);
	map.insert(x);
	DFN[x] = Time; Low[x] = Time;
	Time++;
	for (int i = 0; i < Edge[x].size(); i++)
		if (DFN[Edge[x][i]] == 0)
		{
			dfs(Edge, DFN, val, Low, St, map, Edge[x][i], Time, color, col, colorVal, root);
			Low[x] = min(Low[x], Low[Edge[x][i]]);
		}
		else if (map.count(Edge[x][i]))
		{
			Low[x] = min(Low[x], Low[Edge[x][i]]);
		}
	if (DFN[x] == Low[x])
	{
		int sum = 0x7fffffff;
		while (St.top() != x)
		{
			map.erase(St.top());
			color[St.top()] = col;
			sum = min(sum, val[St.top()]);
			St.pop();
		}
		map.erase(St.top()); colorVal.push_back(min(sum, val[St.top()])); root.push_back(St.top());
		color[St.top()] = col++; St.pop();
	}
}

vector<vector<int>> Tarjan(const vector<vector<int>>& Edge, vector<int>& val, int n, int& col, vector<int>& colorVal, vector<int>& root)
{
	vector<int>DFN(n + 1), Low(n + 1), Color(n + 1);
	unordered_set<int>map;
	stack<int>St;
	int Time = 1;
	for (int i = 1; i <= n; i++)
		if (!DFN[i])
			dfs(Edge, DFN, val, Low, St, map, i, Time, Color, col, colorVal, root);
	vector<vector<int>>newEdge(n + 1);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j < Edge[i].size(); j++)
		{
			if (Color[i] != Color[Edge[i][j]])
				newEdge[Color[i]].push_back(Color[Edge[i][j]]);
		}
	}
	return newEdge;
}

void topologicalSort(const vector<vector<int>>& Edge, int n, vector<int>& colorVal)
{
	unordered_map<int, int>indegree;
	for (int i = 1; i <= n; i++)
		indegree[i] = 0;
	queue<int>Qu;
	for (int i = 1; i <= n; i++)
		for (int j = 0; j < Edge[i].size(); j++)
			indegree[Edge[i][j]]++;

	for (int i = 1; i <= n; i++)
		if (indegree[i] == 0)
			Qu.push(i);
	while (!Qu.empty())
	{
		int selected = Qu.front(); Qu.pop();
		for (int j = 0; j < Edge[selected].size(); j++)
		{
			indegree[Edge[selected][j]]--;
			if (colorVal[selected] != 0x7fffffff)
				colorVal[Edge[selected][j]] = 0;
			if (!indegree[Edge[selected][j]])
				Qu.push(Edge[selected][j]);
		}
	}
}

int main()
{
	int n = read(), p = read();
	vector<int>val(n + 1, 0x7fffffff);
	int u, w;
	for (int i = 1; i <= p; i++)
	{
		u = read(); w = read();
		val[u] = w;
	}
	int r = read();
	vector<vector<int>>testEdge(n + 1);
	for (int i = 1; i <= r; i++)
	{
		u = read(); w = read();
		testEdge[u].push_back(w);
	}

	int col = 1;
	vector<int>colorVal(1), root(1);
	vector<vector<int>>newEdge = Tarjan(testEdge, val, n, col, colorVal, root);

	topologicalSort(newEdge, col - 1, colorVal);
	int ans = 0, Min = -1;
	for (int i = 1; i < col; i++)
	{
		if (colorVal[i] == 0x7fffffff)
		{
			if (Min == -1)
				Min = root[i];
			else
				Min = min(root[i], Min);
		}
		else
			ans += colorVal[i];
	}
	if (Min != -1)
		printf("NO\n%d", Min);
	else
		printf("YES\n%d", ans);
	return 0;
}