#include <iostream>
using namespace std;
int Map[101][101], V, E, closest[101], lowcost[101], sum = 1, ans;
bool Flag[101];
int main()
{
	cin >> V >> E;
	for (int i = 1; i <= V; i++)
		for (int j = 1; j <= V; j++)
			Map[i][j] = 0x7fffffff;
	for (int i = 1; i <= E; i++)
	{
		int Start, End;
		cin >> Start >> End;
		cin >> Map[Start][End];
		Map[End][Start] = Map[Start][End];
	}
	Flag[1] = true;
	closest[1] = 1;
	for (int i = 2; i <= V; i++)
	{
		closest[i] = 1;
		lowcost[i] = Map[1][i];
	}
	while (sum <= V)
	{
		int Min = 0x7ffffff, Num = -1;
		for (int i = 2; i <= V; i++)
		{
			if (!Flag[i])
			{
				if (Min > lowcost[i])
				{
					Min = lowcost[i];
					Num = i;
				}
			}
		}
		Flag[Num] = true;
		for (int i = 2; i <= V; i++)
			if (!Flag[i])
			{
				if (Map[Num][i] < lowcost[i])
				{
					lowcost[i] = Map[Num][i];
					closest[i] = Num;
				}
			}
		sum++;
	}
	cout << "closest: ";
	for (int i = 1; i <= V; i++)
		cout << closest[i] << " ";
	cout << endl << "lowcost: ";
	for (int i = 1; i <= V; i++)
	{
		cout << lowcost[i] << " ";
		ans += lowcost[i];
	}
	cout << endl << "×Ü·ÑÓÃ:" << ans;
}