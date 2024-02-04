#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <unordered_set>
#include <unordered_map>
using namespace std;

void dfs(const vector<vector<int>>& Edge, vector<int>& DFN, vector<int>& Low, stack<int>& St, unordered_set<int>& map, int x, int& Time, vector<int>& color, int& col, vector<int>& colorVal)
{
	St.push(x);
	map.insert(x);
	DFN[x] = Time; Low[x] = Time;
	Time++;
	for (int i = 0; i < Edge[x].size(); i++)
		if (DFN[Edge[x][i]] == 0)
		{
			dfs(Edge, DFN, Low, St, map, Edge[x][i], Time, color, col,colorVal);
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

void topologicalSort(const vector<vector<int>>& Edge, int X, int n, vector<int>colorVal, vector<int>& len, vector<int>& num)
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
		{
			Qu.push(i);
			len[i] = colorVal[i];
			num[i] = 1;
		}
	while (!Qu.empty())
	{
		int Len = Qu.size();
		int selected = Qu.front(); Qu.pop();
		for (int j = 0; j < Edge[selected].size(); j++)
		{
			if (len[Edge[selected][j]] < len[selected] + colorVal[Edge[selected][j]])
			{
				len[Edge[selected][j]] = len[selected] + colorVal[Edge[selected][j]];
				num[Edge[selected][j]] = num[selected];
			}
			else if (len[Edge[selected][j]] == len[selected] + colorVal[Edge[selected][j]])
				num[Edge[selected][j]] = (num[Edge[selected][j]] % X + num[selected] % X) % X;
			indegree[Edge[selected][j]]--;
			if (!indegree[Edge[selected][j]])
				Qu.push(Edge[selected][j]);
		}
	}
}

int main()
{
	int n, m, X;
	scanf("%d %d %d", &n, &m, &X);
	vector<vector<int>>testEdge(n + 1);
	int u, v;
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d", &u, &v);
		testEdge[u].push_back(v);
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

	vector<int>len(col), num(col);
	topologicalSort(newEdge, X, col - 1, colorVal, len, num);
	int maxn1 = -1, maxn2 = -1;
	for (int i = 1; i < col; i++) {
		if (len[i] > maxn1) {
			maxn1 = len[i];
			maxn2 = num[i];
		}
		else if (len[i] == maxn1) {
			maxn2 = (maxn2 % X + num[i] % X) % X;
		}
	}
	printf("%d\n%d\n", maxn1, maxn2);
	return 0;
}