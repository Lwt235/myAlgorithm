#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;
vector<int> topologicalSort(const vector<vector<int>>& Edge, const vector<int>& nodes)
{
	vector<int>ans;
	unordered_map<int, int>indegree;
	for (int i = 0; i < nodes.size(); i++)
		indegree[nodes[i]] = 0;
	queue<int>Qu;
	for (int i = 0; i < nodes.size(); i++)
		for (int j = 0; j < Edge[nodes[i]].size(); j++)
			indegree[Edge[nodes[i]][j]]++;

	for (int i = 0; i < nodes.size(); i++)
		if (indegree[nodes[i]] == 0)
			Qu.push(nodes[i]);
	while (!Qu.empty())
	{
		int selected = Qu.front(); Qu.pop();
		ans.push_back(selected);
		for (int j = 0; j < Edge[selected].size(); j++)
		{
			indegree[Edge[selected][j]]--;
			if (!indegree[Edge[selected][j]])
				Qu.push(Edge[selected][j]);
		}
	}
	return ans;
}
int main()
{
	vector<vector<int>>testEdges(6);
	testEdges[5].push_back(2);
	testEdges[5].push_back(0);
	testEdges[4].push_back(0);
	testEdges[4].push_back(1);
	testEdges[2].push_back(3);
	testEdges[3].push_back(1);
	vector<int>nodes = { 0,1,2,3,4,5 };
	vector<int>ans = topologicalSort(testEdges, nodes);
	for (int i = 0; i < ans.size(); i++)
		cout << ans[i] << " ";
}