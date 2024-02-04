#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <set>
#include <map>
#include <cstring>
#include <stdlib.h>
#include <cstdio>
#define MOD 1000000007
#define INF 2000000000
using namespace std;
inline long long read()
{
    long long x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}
struct edge {
    int To;
    int Weight;
    edge(int To = 0, int Weight = 0) : To(To), Weight(Weight) {};
};
vector<vector<edge>>Edge;
vector<bool>vis;
vector<int>father, ans;
vector<vector<pair<int, int>>>query;
int find(int u)
{
    if (u == father[u]) return u;
    return father[u] = find(father[u]);
}
void Tarjan(int u)
{
    vis[u] = true;
    for (int i = 0; i < Edge[u].size(); i++)
    {
        int v = Edge[u][i].To;
        if (vis[v]) continue;
        Tarjan(v);
        father[v] = u;
    }
    for (int i = 0; i < query[u].size(); i++)
        if (vis[query[u][i].first]) ans[query[u][i].second] = find(query[u][i].first);
}
int main()
{
    int N = read(), M = read(), S = read();
    vector<bool>(N + 1, false).swap(vis);
    vector<vector<edge>>(N + 1).swap(Edge);
    vector<int>(N + 1).swap(father);
    vector<vector<pair<int, int>>>(N + 1).swap(query);
    vector<int>(M + 1).swap(ans);
    for (int i = 1; i <= N; i++)
        father[i] = i;
    for (int i = 1; i < N; i++)
    {
        int x = read(), y = read();
        Edge[x].emplace_back(y);
        Edge[y].emplace_back(x);
    }
    for (int i = 1; i <= M; i++)
    {
        int a = read(), b = read();
        query[a].emplace_back(b, i);
        query[b].emplace_back(a, i);
    }
    Tarjan(S);
    for (int i = 1; i <= M; i++)
        printf("%d\n", ans[i]);
}