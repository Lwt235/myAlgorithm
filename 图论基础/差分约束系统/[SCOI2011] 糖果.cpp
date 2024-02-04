#include <iostream>
#include <vector>
#include <queue>
#define INF 10000000000
using namespace std;

struct edge {
	int to;
	long long weight;
	edge() {};
	edge(int to, int weight) :to(to), weight(weight) {};
};

struct node {
	int to;
	long long step;
	node() {};
	node(int to, long long step) :to(to), step(step) {};
	bool operator < (const node& a) const {
		return step > a.step;
	}
};

long long SPFA(const vector<vector<edge>>& Edge, int n, int start)
{
	vector<long long>dist(n + 1), cnt(n + 1, 0);
	vector<bool>vis(n + 1, false);
	queue<int>Qu;
	dist[start] = 0; vis[start] = true;
	Qu.push(start);
	while (!Qu.empty())
	{
		int selected = Qu.front(); Qu.pop();
		vis[selected] = false;
		for (int i = 0; i < Edge[selected].size(); i++)
		{
			if (dist[selected] + Edge[selected][i].weight > dist[Edge[selected][i].to])
			{
				dist[Edge[selected][i].to] = dist[selected] + Edge[selected][i].weight;
				cnt[Edge[selected][i].to]++;
				if (cnt[Edge[selected][i].to] >= n)
					return INF;
				if (!vis[Edge[selected][i].to])
				{
					Qu.push(Edge[selected][i].to);
					vis[Edge[selected][i].to] = true;
				}
			}
		}
	}
	long long Sum = 0;
	for (int i = 1; i <= n; i++)
	{
		if (dist[i] == INF)
			return INF;
		Sum += dist[i];
	}
	return Sum;
}

int main()
{
	int n, m;
	scanf("%d %d", &n, &m);
	vector<vector<edge>>testEdge(n + 1);
	long long k, u, v;
	bool Key = true;
	for (int i = 0; i < m; i++)
	{
		scanf("%lld %lld %lld", &k, &u, &v);
		if (Key)
		{
			switch (k)
			{
			case 1:
				testEdge[u].push_back(edge(v, 0));
				testEdge[v].push_back(edge(u, 0));
				break;
			case 2:
				testEdge[u].push_back(edge(v, 1));
				break;
			case 3:
				testEdge[v].push_back(edge(u, 0));
				break;
			case 4:
				testEdge[v].push_back(edge(u, 1));
				break;
			case 5:
				testEdge[u].push_back(edge(v, 0));
				break;
			}
			if ((u == v) && (k == 2 || k == 4))
				Key = false;
		}
	}
	if (!Key)
	{
		printf("-1");
		return 0;
	}
	for (int i = 1; i <= n; i++)
		testEdge[0].push_back(edge(i, 1));

	long long ans = SPFA(testEdge, n, 0);
	if (ans == INF)
		printf("-1");
	else
		printf("%lld", ans);
}