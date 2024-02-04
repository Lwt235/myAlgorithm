#include <iostream>
#include <algorithm>
using namespace std;
int V, E, ans, Node[101], sum;
struct Edge {
	int Start;
	int End;
	int Value;
	Edge() : Start(0), End(0), Value(0) {};
	Edge(int Start, int End, int Value) : Start(Start), End(End), Value(Value) {};
}edge[101];
bool Cmp(Edge q, Edge p)
{
	return q.Value < p.Value;
}
int main()
{
	cin >> V >> E;
	for (int i = 1; i <= E; i++)
	{
		int Start, End, Value;
		cin >> Start >> End >> Value;
		edge[i] = Edge(Start, End, Value);
	}
	sort(edge + 1, edge + E + 1, Cmp);
	for (int i = 1; i <= V; i++)
		Node[i] = i;
	for(int i=1;i<=E;i++)
	{
		if (sum >= V)
			break;
		if (Node[edge[i].Start] != Node[edge[i].End])
		{
			ans += edge[i].Value;
			if (Node[edge[i].End] < Node[edge[i].Start])
			{
				int temp = Node[edge[i].Start];
				for (int j = 1; j <= V; j++)
					if (Node[j] == temp)
						Node[j] = Node[edge[i].End];
			}
			else
			{
				int temp = Node[edge[i].End];
				for (int j = 1; j <= V; j++)
					if (Node[j] == temp)
						Node[j] = Node[edge[i].Start];
			}
			sum++;
		}
	}
	cout << "×Ü»¨·Ñ" << ans;
}