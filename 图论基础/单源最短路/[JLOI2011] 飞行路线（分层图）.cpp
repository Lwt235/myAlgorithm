#include <iostream>
#include <vector>
#include <queue>
#define INF 1000000000
using namespace std;

struct edge {
	int To;
	int weight;
	edge() {};
	edge(int To, int weight) :To(To), weight(weight) {};
};

struct node {
	int To;
	int step;
	node() {};
	node(int To = -1, int step = -1) :To(To), step(step) {};
	bool operator < (const node& a) const {
		return step > a.step;
	}
};

int n, m;
vector<vector<edge>>Edge;
vector<int>dist;

int read()
{
	int x = 0;
	char c = getchar();
	while (c < '0' || c > '9') c = getchar();
	while (c >= '0' && c <= '9')
	{
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = getchar();
	}
	return x;
}

void Dijkstra(int start)
{
	priority_queue<node>Qu;
	vector<bool>vis(dist.size(), false);
	Qu.emplace(start, 0);
	dist[start] = 0;
	while (!Qu.empty())
	{
		int u = Qu.top().To; Qu.pop();
		if (vis[u])
			continue;
		vis[u] = true;
		for (int i = 0; i < Edge[u].size(); i++)
		{
			int v = Edge[u][i].To;
			if (!vis[v] && dist[u] != INF && dist[u] + Edge[u][i].weight < dist[v])
			{				
				dist[v] = dist[u] + Edge[u][i].weight;
				Qu.emplace(v, dist[v]);
			}
		}
	}
}

int main()
{
	int n = read(), m = read(), k = read();
	int s = read(), t = read();
	int a, b, c;
	vector<vector<edge>>((k + 1) * n).swap(Edge);
	vector<int>((k + 1) * n, INF).swap(dist);
	for (int i = 0; i < m; i++)
	{
		a = read(); b = read(); c = read();
		for (int j = 0; j <= k; j++)
		{
			Edge[a + j * n].emplace_back(b + j * n, c);
			Edge[b + j * n].emplace_back(a + j * n, c);
		}
		
		for (int j = 1; j <= k; j++)
		{
			Edge[a + j * n - n].emplace_back(b + j * n, 0);
			Edge[b + j * n - n].emplace_back(a + j * n, 0);
		}
	}
	for (int i = 1; i <= k; i++)
		Edge[(i - 1) * n + t].emplace_back(i * n + t, 0);
	Dijkstra(s);
	cout << dist[k * n + t];
	return 0;
}