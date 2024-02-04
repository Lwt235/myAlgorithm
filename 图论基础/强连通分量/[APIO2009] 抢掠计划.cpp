#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <unordered_set>
#include <unordered_map>
using namespace std;
vector<vector<int>>Edge;
vector<int>DFN, Low, Color;
vector<pair<int, bool>>val, colorVal(1);
unordered_set<int>map;
stack<int>St;
int col = 1, n, m, Time = 1;
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

void dfs(int x)
{
	St.push(x);
	map.insert(x);
	DFN[x] = Time; Low[x] = Time;
	Time++;
	for (int i = 0; i < Edge[x].size(); i++)
		if (DFN[Edge[x][i]] == 0)
		{
			dfs(Edge[x][i]);
			Low[x] = min(Low[x], Low[Edge[x][i]]);
		}
		else if (map.count(Edge[x][i]))
		{
			Low[x] = min(Low[x], Low[Edge[x][i]]);
		}
	if (DFN[x] == Low[x])
	{
		int sum = 0;
		bool isbar = false;
		while (St.top() != x)
		{
			map.erase(St.top());
			Color[St.top()] = col;
			sum += val[St.top()].first;
			isbar |= val[St.top()].second;
			St.pop();
		}
		map.erase(St.top()); colorVal.push_back(make_pair(sum + val[St.top()].first, isbar | val[St.top()].second));
		Color[St.top()] = col++; St.pop();
	}
	
}

void Tarjan()
{
	
	for (int i = 1; i <= n; i++)
		if (!DFN[i])
			dfs(i);
	vector<vector<int>>newEdge(col);
	for (int i = 1; i <= n; i++)
		for (int j = 0; j < Edge[i].size(); j++)
			if (Color[i] != Color[Edge[i][j]])
				newEdge[Color[i]].push_back(Color[Edge[i][j]]);
	Edge = newEdge;
}

int SPFA(vector<pair<int, bool>>& val, int n, int start)
{
	vector<int>dist(n + 1);
	vector<bool>vis(n + 1, false);
	queue<int>Qu;
	dist[start] = val[start].first; vis[start] = true;
	Qu.push(start);
	int Ans = 0;
	while (!Qu.empty())
	{
		int selected = Qu.front(); Qu.pop(); vis[selected] = false;
		if (val[selected].second)
			Ans = max(Ans, dist[selected]);
		for (int i = 0; i < Edge[selected].size(); i++)
		{
			if (dist[selected] + val[Edge[selected][i]].first > dist[Edge[selected][i]])
			{
				dist[Edge[selected][i]] = dist[selected] + val[Edge[selected][i]].first;
				if (!vis[Edge[selected][i]])
				{
					Qu.push(Edge[selected][i]);
					vis[Edge[selected][i]] = true;
				}
			}
		}
	}
	return Ans;
}

int main()
{
	n = read(); m = read();
	vector<vector<int>>(n + 1).swap(Edge);
	vector<int>(n + 1).swap(DFN); vector<int>(n + 1).swap(Low); vector<int>(n + 1).swap(Color);
	int u, v;
	for (int i = 1; i <= m; i++)
	{
		u = read(); v = read();
		Edge[u].push_back(v);
	}
	vector<pair<int, bool>>(n + 1).swap(val);
	for (int i = 1; i <= n; i++)
		val[i].first = read();
	int s = read(), p = read(), tmp;
	for (int i = 1; i <= p; i++)
	{
		tmp = read();
		val[tmp].second = true;
	}
	Tarjan();
	printf("%d", SPFA(colorVal, col - 1, Color[s]));
}