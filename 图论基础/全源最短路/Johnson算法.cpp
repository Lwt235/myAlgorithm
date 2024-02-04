#include <iostream>
#include <vector>
#include <queue>
#define INF 1000000
using namespace std;
struct edge {
	int to;
	int weight;
	edge() {};
	edge(int to, int weight) :to(to), weight(weight) {};
};

struct node {
	int to;
	int step;
	node() {};
	node(int to, int step) :to(to), step(step) {};
	bool operator < (const node& a)const {
		return step > a.step;
	}
};

vector<int> Dijkstra(const vector<vector<edge>>& Edge, int n, int start)
{
	vector<int>dist(n + 1, INF);
	vector<bool>vis(n + 1, false);
	priority_queue<node>Qu;
	dist[start] = 0; Qu.push(node(start, 0));
	while (!Qu.empty())
	{
		node selected = Qu.top(); Qu.pop();
		if (vis[selected.to])
			continue;
		vis[selected.to] = true;
		for (int i = 0; i < Edge[selected.to].size(); i++)
		{
			if (!vis[Edge[selected.to][i].to])
				if (dist[selected.to] != INF && dist[selected.to] + Edge[selected.to][i].weight < dist[Edge[selected.to][i].to])
				{
					dist[Edge[selected.to][i].to] = dist[selected.to] + Edge[selected.to][i].weight;
					Qu.push(node(Edge[selected.to][i].to, dist[Edge[selected.to][i].to]));
				}
		}
	}
	return dist;
}

vector<int> SPFA(const vector<vector<edge>>& Edge, int n, int start)
{
	vector<int>dist(n + 1, INF), cnt(n + 1, 0);
	vector<bool>vis(n + 1, false);
	queue<int>Qu;
	dist[start] = 0; cnt[start] = 1; vis[start] = true;
	Qu.push(start);
	while (!Qu.empty())
	{
		int selected = Qu.front(); Qu.pop(); vis[selected] = false;
		for (int i = 0; i < Edge[selected].size(); i++)
		{
			if (dist[selected] != INF && dist[selected] + Edge[selected][i].weight < dist[Edge[selected][i].to])
			{
				dist[Edge[selected][i].to] = dist[selected] + Edge[selected][i].weight;
				cnt[Edge[selected][i].to]++;
				if (cnt[Edge[selected][i].to] >= n)
					return {};
				if (!vis[Edge[selected][i].to])
				{
					vis[Edge[selected][i].to] = true;
					Qu.push(Edge[selected][i].to);
				}
			}
		}
	}
	return dist;
}

/*

Johnson算法：
在维持Heap-Dijkstra原有时间复杂度O(nmlogn)的基础上解决了Dijkstra不能处理负权边的问题

基础：
Heap-Dijkstra
SPFA

*/
vector<vector<int>> Johnson(vector<vector<edge>>& Edge, int n)
{
	for (int i = 1; i <= n; i++)
		Edge[0].push_back(edge(i, 0));
	vector<int>dist = SPFA(Edge, n, 0);
	if (dist.empty())
		return {};
	Edge[0] = {};
	for (int u = 1; u <= n; u++)
		for (int i = 0; i < Edge[u].size(); i++)
			Edge[u][i].weight += dist[u] - dist[Edge[u][i].to];
	
	vector<vector<int>>ans = { {} };
	for (int u = 1; u <= n; u++)
	{
		ans.push_back(Dijkstra(Edge, n, u));
		for (int i = 1; i <= n; i++)
			if (ans[u][i] != INF)
				ans[u][i] -= dist[u] - dist[i];
	}
	return ans;
}

int main()
{
	int n, m;
	cin >> n >> m;
	vector<vector<edge>>Edge(n + 1);
	int u, v, w;
	for (int i = 0; i < m; i++)
	{
		cin >> u >> v >> w;
		Edge[u].push_back(edge(v, w));
	}
	vector<vector<int>> ans = Johnson(Edge, n);
	if (ans.empty())
	{
		cout << "存在负环，无解" << endl;
		return 0;
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
			if (ans[i][j] == INF)
				cout << "INF ";
			else
				cout << ans[i][j] << " ";
		cout << endl;
	}
}