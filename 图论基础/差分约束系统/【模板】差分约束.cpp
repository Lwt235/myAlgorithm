#include <iostream>
#include <vector>
#include <queue>
#define INF 1000000000
using namespace std;

struct edge {
	int to;
	int weight;
	edge() {};
	edge(int to, int weight) :to(to), weight(weight) {};
};

vector<int> SPFA(const vector<vector<edge>>& Edge, int n, int start)
{
	vector<int>dist(n + 1, INF), cnt(n + 1, 0);
	vector<bool>vis(n + 1, false);
	queue<int>Qu;
	dist[start] = 0; vis[start] = true; cnt[start] = 1;
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
					Qu.push(Edge[selected][i].to);
					vis[Edge[selected][i].to] = true;
				}
			}
		}
	}
	return dist;
}



int main()
{
	int n, m;
	cin >> n >> m;

	vector<vector<edge>>testEdge(n + 1);
	int u, v, w;
	for (int i = 1; i <= n; i++)
		testEdge[0].push_back(edge(i, 0));
	for (int i = 0; i < m; i++)
	{
		cin >> u >> v >> w;
		testEdge[v].push_back(edge(u, w));
	}

	vector<int>ans = SPFA(testEdge, n, 0);
	if (ans.empty())
	{
		cout << "NO" << endl;
		return 0;
	}
	else
	{
		for (int i = 1; i <= n; i++)
			cout << ans[i] << " ";
	}
}