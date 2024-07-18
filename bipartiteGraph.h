#pragma once
#ifndef _BIPARTITEGRAPH_
#define _BIPARTITEGRAPH_

#ifndef _BASICGRPAH_
#include "basicGraph.h"
#endif

#ifndef _FUNCTIONAL_
#include <functional>
#endif

int bipartiteGraphMatching(int n, int m, const std::vector<std::vector<int>>& adjacencyMatrix, int INF = std::numeric_limits<int>::max()) {
	int ans = 0;
	std::vector<bool>vis(m + 1, false);
	std::vector<int>match(m + 1);
	std::function<bool(const int&)>dfs;
	dfs = [&](const int& u) {
		for (int v = 1; v <= m; v++) if (adjacencyMatrix[u][v] != INF) {
			if (vis[v]) continue;
			vis[v] = true;
			if (!match[v] || dfs(match[v])) {
				match[v] = u;
				return true;
			}
		}
		return false;
	};
	for (int i = 1; i <= n; i++) {
		std::vector<bool>(m + 1, false).swap(vis);
		if (dfs(i)) ans++;
	}
	return ans;
}

template <typename T>
T maxBipartiteGraphMatching(int n, int m, const std::vector<std::vector<T>>& adjacencyMatrix, const T INF = std::numeric_limits<T>::max(), const T nINF = std::numeric_limits<T>::min()) {
	std::vector<int>match(m + 1);
	std::vector<bool>va(n + 1, false), vb(m + 1, false);
	std::vector<T>la(n + 1, nINF), lb(m + 1), d(m + 1);
	std::function<bool(int)>dfs;
	dfs = [&](int x) {
		va[x] = true;
		for (int y = 1; y <= m; y++) {
			T weight = adjacencyMatrix[x][y];
			if (!vb[y]) {
				if (la[x] + lb[y] - weight == 0) {
					vb[y] = true;
					if (!match[y] || dfs(match[y])) {
						match[y] = x;
						return true;
					}
				}
				else d[y] = std::min(d[y], la[x] + lb[y] - weight);
			}
		}
		return false;
	};
	
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			la[i] = std::max(la[i], adjacencyMatrix[i][j]);
	for (int i = 1; i <= n; i++) {
		while (true) {
			std::vector<bool>(n + 1, false).swap(va);
			std::vector<bool>(m + 1, false).swap(vb);
			std::vector<T>(m + 1, INF).swap(d);
			if (dfs(i)) break;
			T delta = INF;
			for (int j = 1; j <= m; j++)
				if (!vb[j]) delta = std::min(delta, d[j]);
			for (int j = 1; j <= n; j++) if (va[j]) la[j] -= delta;
			for (int j = 1; j <= m; j++) if (vb[j]) lb[j] += delta;
		}
	}
	T res = adjacencyMatrix[match[1]][1];
	for (int i = 2; i <= m; i++) {
		res += adjacencyMatrix[match[i]][i];
	}
	return res;
}

#endif // !_BIPARTITEGRAPH_
