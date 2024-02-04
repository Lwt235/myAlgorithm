#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
vector<vector<int>>Edge, Bridge;
vector<int>DFN, Low, Father;
vector<bool>Points;
int n, m, Time = 1, tot = 0;
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

void Tarjan(int x)
{
	DFN[x] = Time; Low[x] = Time;
	Time++;
	int child = 0;
	for (int i = 0; i < Edge[x].size(); i++)
	{
		int To = Edge[x][i];
		if (!DFN[To])
		{
			Father[To] = x; child++;
			Tarjan(To);
			Low[x] = min(Low[x], Low[To]);


			if (Father[x] != -1 && DFN[x] <= Low[To])
			{
				tot += !Points[x];
				Points[x] = true;
			}
			if (Father[x] == -1 && child >= 2)
			{
				tot += !Points[x];
				Points[x] = true;
			}
			if (Low[To] > DFN[x])
				Bridge[x].push_back(To);
		}
		else if (To != Father[x])
			Low[x] = min(Low[x], DFN[To]);
	}

}

int main()
{
	n = read(), m = read();
	vector<vector<int>>(n + 1).swap(Edge); vector<vector<int>>(n + 1).swap(Bridge);
	vector<int>(n + 1).swap(DFN); vector<int>(n + 1).swap(Low); vector<int>(n + 1, -1).swap(Father);
	vector<bool>(n + 1).swap(Points);
	int i, j;
	for (int k = 0; k < m; k++)
	{
		i = read(); j = read();
		Edge[i].push_back(j);
		Edge[j].push_back(i);
	}
	for (int i = 1; i <= n; i++)
		if (!DFN[i]) Tarjan(i);
	/*cout << "割点有" << tot << "个，包括:" << endl;*/
	cout << tot << endl;
	for (int i = 1; i <= n; i++)
	{
		if (Points[i])
			cout << i << " ";
	}
	/*cout << endl << "桥包括: " << endl;
	for (int i = 1; i <= n; i++)
		for (int j = 0; j < Bridge[i].size(); j++)
			cout << i << "-" << Bridge[i][j] << endl;*/
}