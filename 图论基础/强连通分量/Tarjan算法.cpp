#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <unordered_set>
using namespace std;

void dfs(const vector<vector<int>>& Edge, vector<int>& DFN, vector<int>& Low, stack<int>& St, unordered_set<int>& map, int x, int& Time, vector<int>& val, vector<int>& color, int& col, vector<int>& colorVal)
{
	St.push(x);
	map.insert(x);
	DFN[x] = Time; Low[x] = Time;
	Time++;
	for (int i = 0; i < Edge[x].size(); i++)
		if (DFN[Edge[x][i]] == 0)
		{
			dfs(Edge, DFN, Low, St, map, Edge[x][i], Time, val, color, col, colorVal);
			Low[x] = min(Low[x], Low[Edge[x][i]]);
		}
		else if (map.count(Edge[x][i]))
		{
			Low[x] = min(Low[x], Low[Edge[x][i]]);
		}
	if (DFN[x] == Low[x])
	{
		long long sum = 0;
		while (St.top() != x)
		{
			map.erase(St.top());
			color[St.top()] = col;
			sum += val[St.top()];
			St.pop();
		}
		map.erase(St.top()); sum += val[St.top()];
		colorVal.push_back(sum); color[St.top()] = col++; St.pop();
	}
}

vector<vector<int>> Tarjan(const vector<vector<int>>& Edge, int n, vector<int>& val, int& col)
{
	vector<int>DFN(n + 1), Low(n + 1), Color(n + 1), colorVal;
	unordered_set<int>map;
	stack<int>St;
	int Time = 1;
	for (int i = 1; i <= n; i++)
		if (!DFN[i])
			dfs(Edge, DFN, Low, St, map, i, Time, val, Color, col, colorVal);
	vector<vector<int>>newEdge(n + 1);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j < Edge[i].size(); j++)
		{
			if (Color[i] != Color[Edge[i][j]])
				newEdge[Color[i]].push_back(Color[Edge[i][j]]);
		}
	}
	val = colorVal;
	return newEdge;
}

int main()
{
	int n, m;
	scanf("%d %d", &n, &m);
	vector<int>val(n + 1);
	for (int i = 1; i <= n; i++)
		scanf("%d", &val[i]);
	vector<vector<int>>testEdge(n + 1);
	int u, v;
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d", &u, &v);
		testEdge[u].push_back(v);
	}

	int col = 1;
	vector<vector<int>>newEdge = Tarjan(testEdge, n, val, col);

	for (int i = 1; i < col; i++)
	{
		cout << i << " val=" << val[i - 1] << " :" << endl;
		for (int j = 0; j < newEdge[i].size(); j++)
		{
			cout << i << " " << newEdge[i][j] << endl;
		}
		cout << endl;
	}
}