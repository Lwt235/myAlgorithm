#include <iostream>
#include <vector>
#include <queue>
#define INF 1000000
using namespace std;

/*

//Bellman-Ford算法所需edge类型格式
struct edge {
	int from;
	int to;
	int weight;
};

*/

//SPFA算法所需edge类型格式
struct edge {
	int to;
	int weight;
	edge() {};
	edge(int to, int weight) :to(to), weight(weight) {};
};

/*

//Bellman-Ford算法
vector<int> Bellman_Ford(const vector<edge>& Edge, int n, int start)
{
	vector<int>dist(n + 1, INF);
	dist[start] = 0;
	for (int i = 1; i < n; i++)
		for (int j = 0; j < Edge.size(); j++)
			if (dist[Edge[j].from] + Edge[j].weight < dist[Edge[j].to])
				dist[Edge[j].to] = dist[Edge[j].from] + Edge[j].weight;
	
	for (int j = 0; j < Edge.size(); j++)
		if (dist[Edge[j].from] + Edge[j].weight < dist[Edge[j].to])
			return {};
	return dist;
}

*/

//SPFA算法
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
	
	/*
	//Bellman-Ford算法所需边集的储存方式
	vector<edge>testEdge(m);
	int u, v, w, start;
	for (int i = 0; i < m; i++)
	{
		cin >> u >> v >> w;
		testEdge[i].from = u;
		testEdge[i].to = v;
		testEdge[i].weight = w;
	}

	*/

	//SPFA算法所需边集的储存方式
	vector<vector<edge>>testEdge(n + 1);
	int u, v, w, start;
	for (int i = 0; i < m; i++)
	{
		cin >> u >> v >> w;
		testEdge[u].push_back(edge(v, w));
	}

	
in:
	cin >> start;
	if (start >= n)
	{
		cout << "无效的输入" << endl;
		goto in;
	}

	//vector<int>ans = Bellman_Ford(testEdge, n, start);
	vector<int>ans = SPFA(testEdge, n, start);

	if (ans.empty())
	{
		cout << "不存在最短路径!" << endl;
		return 0;
	}
	else
	{
		cout << "起点为" << start << "的最短路径如下:" << endl;
		//默认从1开始编号
		for (int i = 1; i <= n; i++)
			if (ans[i] == INF)
				cout << "INF ";
			else
				cout << ans[i] << " ";
		cout << endl;
	}
}

/*
---------------
Test 0:

in:
5 8
1 2 -1
1 3 3
2 4 2
3 2 4
3 4 7
3 5 4
4 3 -6
4 5 5
1

out:
起点为1的最短路径如下:
0 -1 -5 1 -1
---------------
Test 1:

in:
3 3
1 2 -1
2 3 -1
3 1 -1
1

out:
不存在最短路径!
---------------
*/