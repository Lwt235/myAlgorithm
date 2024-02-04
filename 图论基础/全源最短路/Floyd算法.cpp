#include <iostream>
#include <vector>
#define INF 1000000
using namespace std;
/*
Floyd算法
时间复杂度为O(n^3)
可以处理负边权，
但不能包含负环
相比Dijkstra更优雅，但是复杂度高于最大堆优化后的Dijkstra
*/
void Floyd(vector<vector<int>>& Dist)
{
	int n = Dist.size() - 1;
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				if (Dist[i][k] != INF && Dist[k][j] != INF)
					Dist[i][j] = min(Dist[i][j], Dist[i][k] + Dist[k][j]);
	return;
}
int main()
{
	int n, m;
	cin >> n >> m;
	int u, v, w;
	vector<vector<int>>Dist(n + 2, vector<int>(n + 2, INF));

	//从0开始计数
	for (int i = 1; i <= n; i++)
		Dist[i][i] = 0;

	for (int i = 0; i < m; i++)
	{
		cin >> u >> v >> w;
		Dist[u][v] = min(Dist[u][v], w);
	}

	Floyd(Dist);

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
			if (Dist[i][j] != INF)
				cout << Dist[i][j] << " ";
			else
				cout << "INF ";
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

out:
0 -1 -5 1 -1
INF 0 -4 2 0
INF 4 0 6 4
INF -2 -6 0 -2
INF INF INF INF 0
---------------
Test 1:

4 8
1 2 4
1 3 8
1 4 6
2 3 3
3 1 7
3 4 9
4 1 5
4 3 3

out:
0 4 7 6
10 0 3 12
7 11 0 9
5 9 3 0
---------------
*/