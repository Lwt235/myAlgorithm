#include <iostream>
#include <vector>
#include <queue>
#define INF 1000000000
using namespace std;
/*
Dijkstra算法(最大堆优化)
时间复杂度O(nlogn)
不能带有负权值的边
不能存在负环
*/
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
	bool operator < (const node& a) const {
		return step > a.step;
	}
};

vector<int> Dijkstra(const vector<vector<edge>>& Edge, int n, int start)
{
	vector<int>dist(n + 1, INF);
	vector<bool>vis(n + 1, false);
	priority_queue<node>Qu;
	dist[start] = 0; Qu.emplace(start, 0);
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
					Qu.emplace(Edge[selected.to][i].to, dist[Edge[selected.to][i].to]);
				}	
		}
	}
	return dist;
}
int main()
{
	int n, m, start;
	cin >> n >> m;
	vector<vector<edge>>Edge(n + 1);
	int u, v, w;
	for (int i = 0; i < m; i++)
	{
		cin >> u >> v >> w;
		Edge[u].push_back(edge(v, w));
	}
	cin >> start;

	vector<int>dist = Dijkstra(Edge, n, start);

	cout << "最短路径如下:" << endl;
	for (int i = 1; i <= n; i++)
	{
		if (dist[i] != INF)
			cout << dist[i] << " ";
		else
			cout << "INF ";
	}
}