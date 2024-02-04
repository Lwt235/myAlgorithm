#include <iostream>
#include <vector>
#include <queue>
#define INF 1e18
using namespace std;

struct edge {
	int To;
	long long weight;
	edge() {};
	edge(int To, long long weight) :To(To), weight(weight) {};
};

struct node {
	int To;
	long long step;
	node() {};
	node(int To = -1, long long step = -1) :To(To), step(step) {};
	bool operator < (const node& a) const {
		return step > a.step;
	}
};

long long n, m, hp;
vector<vector<edge>>Edge;
vector<long long>dist, val;

int read()
{
	long long x = 0;
	char c = getchar();
	while (c < '0' || c > '9') c = getchar();
	while (c >= '0' && c <= '9')
	{
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = getchar();
	}
	return x;
}

void Dijkstra(int start, long long tar)
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
			if (!vis[v] && val[v] <= tar && Edge[u][i].weight != INF && dist[u] + Edge[u][i].weight < dist[v])
			{				
				dist[v] = dist[u] + Edge[u][i].weight;
				Qu.emplace(v, dist[v]);
			}
		}
	}
}

int main()
{
	int n = read(), m = read();
	long long hp = read();
	int a, b, c;
	long long Max;
	vector<vector<edge>>(n + 1).swap(Edge);
	vector<long long>(n + 1).swap(val);
	for (int i = 1; i <= n; i++)
	{
		val[i] = read();
		Max = max(Max, val[i]);
	}
	for (int i = 0; i < m; i++)
	{
		a = read(); b = read(); c = read();
		Edge[a].emplace_back(b, c);
		Edge[b].emplace_back(a, c);
	}
	long long Left = 1, Right = Max, Middle;
	bool flag = false;
	while (Left <= Right)
	{
		Middle = (Left + Right) / 2;
		vector<long long>(n + 1, INF).swap(dist);
		Dijkstra(1, Middle);
		if (Middle < val[1] || dist[n] > hp)
			Left = Middle + 1;
		else
		{
			Right = Middle - 1;
			flag = true;
		}
	}
	if (flag)
		printf("%d", Left);
	else
		printf("AFK");
	return 0;
}