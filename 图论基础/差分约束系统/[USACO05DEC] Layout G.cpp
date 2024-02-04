//#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
#include <queue>
#define INF 10000000000
using namespace std;

struct edge {
	int to;
	long long weight;
	edge() {};
	edge(int to, long long weight) :to(to), weight(weight) {};
};

long long SPFA(const vector<vector<edge>>& Edge, int n, int start)
{
	vector<long long>dist(n + 1, INF), cnt(n + 1, 0);
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
			if (dist[selected] < INF && dist[selected] + Edge[selected][i].weight < dist[Edge[selected][i].to])
			{
				dist[Edge[selected][i].to] = dist[selected] + Edge[selected][i].weight;
				cnt[Edge[selected][i].to]++;
				if (cnt[Edge[selected][i].to] >= n)
					return -1;
				if (!vis[Edge[selected][i].to])
				{
					Qu.push(Edge[selected][i].to);
					vis[Edge[selected][i].to] = true;
				}
			}
		}
	}
	if (dist[n] == INF)
		return -2;
	else
		return dist[n];
}

int main()
{
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);
	vector<vector<edge>>testEdge(n + 1);
	int w, u, v;
	bool Key = true;
	for (int i = 1; i < n; i++)
	{
		testEdge[i + 1].push_back(edge(i, 0));
	}
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d %d", &u, &v, &w);
		testEdge[u].push_back(edge(v, w));
	}
	for (int i = 0; i < k; i++)
	{
		scanf("%d %d %d", &u, &v, &w);
		testEdge[v].push_back(edge(u, -w));
	}
	for (int i = 1; i <= n; i++)
		testEdge[0].push_back(edge(i, 0));
	if (SPFA(testEdge, n, 0) == -1)
	{
		printf("-1");
		return 0;
	}
	testEdge[0] = {};
	printf("%lld", SPFA(testEdge, n, 1));
}