#include <cstdio>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>
using namespace std;
vector<vector<int>>Edge;
vector<int>DFN, Low, Color;
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
		while (St.top() != x)
		{
			map.erase(St.top());
			Color[St.top()] = col;
			St.pop();
		}
		map.erase(St.top());
		Color[St.top()] = col++; St.pop();
	}

}

void Tarjan()
{
	for (int i = 1; i <= (n << 1); i++)
		if (!DFN[i])
			dfs(i);
}
int main()
{
	n = read(), m = read();
	vector<vector<int>>((n << 1) + 1).swap(Edge);
	vector<int>((n << 1) + 1).swap(DFN); vector<int>((n << 1) + 1).swap(Low); vector<int>((n << 1) + 1).swap(Color);
	int i, j;
	for (int k = 0; k < m; k++)
	{
		i = read(); j = read();
		Edge[i].push_back(((j - 1) ^ 1) + 1); Edge[j].push_back(((i - 1) ^ 1) + 1);
	}
	Tarjan();
	for (int i = 1; i <= (n << 1); i += 2)
		if (Color[i] == Color[i + 1])
		{
			printf("NIE\n");
			return 0;
		}
	for (int i = 1; i <= (n << 1); i += 2)
		printf("%d\n", (Color[i] < Color[((i - 1) ^ 1) + 1]) ? i : ((i - 1) ^ 1) + 1);
}