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

void dfs(const vector<vector<int>>& Edge, vector<int>& DFN, vector<int>& Low, stack<int>& St, unordered_set<int>& map, int x, int& Time, vector<int>& color, int& col, vector<int>& colorVal)
{
	St.push(x);
	map.insert(x);
	DFN[x] = Time; Low[x] = Time;
	Time++;
	for (int i = 0; i < Edge[x].size(); i++)
		if (DFN[Edge[x][i]] == 0)
		{
			dfs(Edge, DFN, Low, St, map, Edge[x][i], Time, color, col, colorVal);
			Low[x] = min(Low[x], Low[Edge[x][i]]);
		}
		else if (map.count(Edge[x][i]))
		{
			Low[x] = min(Low[x], Low[Edge[x][i]]);
		}
	if (DFN[x] == Low[x])
	{
		int sum = 0;
		while (St.top() != x)
		{
			map.erase(St.top());
			color[St.top()] = col;
			sum++;
			St.pop();
		}
		map.erase(St.top()); colorVal.push_back(sum + 1);
		color[St.top()] = col++; St.pop();
	}
}

vector<vector<int>> Tarjan(const vector<vector<int>>& Edge, int n, int& col, vector<int>& colorVal)
{
	vector<int>DFN(n + 1), Low(n + 1), Color(n + 1);
	unordered_set<int>map;
	stack<int>St;
	int Time = 1;
	for (int i = 1; i <= n; i++)
		if (!DFN[i])
			dfs(Edge, DFN, Low, St, map, i, Time, Color, col, colorVal);
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

void topologicalSort(const vector<vector<int>>& Edge, int n, vector<int>colorVal, int& planA, int& planB)
{
	unordered_map<int, int>indegree, outdegree;
	for (int i = 1; i <= n; i++)
	{
		indegree[i] = 0;
		outdegree[i] = 0;
	}
	queue<int>Qu;
	for (int i = 1; i <= n; i++)
	{
		outdegree[i] = Edge[i].size();
		for (int j = 0; j < Edge[i].size(); j++)
			indegree[Edge[i][j]]++;
	}

	for (int i = 1; i <= n; i++)
		if (indegree[i] == 0)
		{
			Qu.push(i);
			planA++;
		}
	int inB = 0, outB = 0;
	while (!Qu.empty())
	{
		int selected = Qu.front(); Qu.pop();
		if (outdegree[selected] == 0)
			outB++;
		for (int j = 0; j < Edge[selected].size(); j++)
		{
			indegree[Edge[selected][j]]--;
			if (!indegree[Edge[selected][j]])
				Qu.push(Edge[selected][j]);
		}
	}
	planB = max(planA, outB);
}

int main()
{
	int n = read();
	vector<vector<int>>testEdge(n + 1);
	for (int i = 1; i <= n; i++)
	{
		int v = read();
		while (v != 0)
		{
			testEdge[i].push_back(v);
			v = read();
		}
	}

	int col = 1;
	vector<int>colorVal(1);
	vector<vector<int>>newEdge = Tarjan(testEdge, n, col, colorVal);

	for (int i = 1; i < col; i++)
	{
		unordered_set<int>tmp;
		for (int j = 0; j < newEdge[i].size(); j++)
		{
			if (tmp.count(newEdge[i][j]))
			{
				newEdge[i].erase(newEdge[i].begin() + j);
				j--;
			}
			else
				tmp.insert(newEdge[i][j]);
		}
	}

	int planA = 0, planB = 0;
	if (col == 2)
	{
		printf("1\n0");
		return 0;
	}
	topologicalSort(newEdge, col - 1, colorVal, planA, planB);
	printf("%d\n%d", planA, planB);
	return 0;
}