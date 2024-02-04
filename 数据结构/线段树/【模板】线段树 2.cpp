#define _CRT_SECURE_NO_WARNINGS 1
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <unordered_set>
#define MOD 571373
using namespace std;
inline long long read()
{
	long long x = 0, f = 1;
	char c = getchar();
	while (c < '0' || c>'9')
	{
		if (c == '-')
			f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9')
	{
		x = (x << 3ll) + (x << 1ll) + (c ^ 48);
		c = getchar();
	}
	return x;
}
struct node {
	int l, r;
	long long sum, add, mul;
	node(int l = -1, int r = -1, long long sum = 0, long long add = 0, long long mul = 1) :l(l), r(r), sum(sum), add(add), mul(mul) {};
};

vector<node>Tree;
vector<long long>Val;

void pushUp(int p)
{
	Tree[p].sum = (Tree[p << 1].sum + Tree[p << 1 | 1].sum) % MOD;
}

void pushDown(int p)
{
	Tree[p << 1].sum = (Tree[p << 1].sum * Tree[p].mul + (Tree[p].add * (Tree[p << 1].r - Tree[p << 1].l + 1) % MOD) % MOD) % MOD;
	Tree[p << 1 | 1].sum = (Tree[p << 1 | 1].sum * Tree[p].mul + (Tree[p].add * (Tree[p << 1 | 1].r - Tree[p << 1 | 1].l + 1) % MOD) % MOD) % MOD;
	Tree[p << 1].mul = (Tree[p << 1].mul * Tree[p].mul) % MOD;
	Tree[p << 1 | 1].mul = (Tree[p << 1 | 1].mul * Tree[p].mul) % MOD;
	Tree[p << 1].add = (Tree[p << 1].add * Tree[p].mul + Tree[p].add) % MOD;
	Tree[p << 1 | 1].add = (Tree[p << 1 | 1].add * Tree[p].mul + Tree[p].add) % MOD;
	Tree[p].mul = 1;
	Tree[p].add = 0;
}

void Build(int p, int l, int r)
{
	Tree[p] = node(l, r, Val[l], 0);
	if (l == r)
		return;
	int m = (l + r) >> 1;
	Build(p << 1, l, m);
	Build(p << 1 | 1, m + 1, r);
	pushUp(p);
}

long long querySearch(int p, int l, int r)
{
	if (Tree[p].l >= l && Tree[p].r <= r)
		return Tree[p].sum;
	int m = (Tree[p].l + Tree[p].r) >> 1;
	long long sum = 0;
	pushDown(p);
	if (l <= m)
		sum = (sum + querySearch(p << 1, l, r)) % MOD;
	if (r > m)
		sum = (sum + querySearch(p << 1 | 1, l, r)) % MOD;
	return sum;
}

void queryUpdatePlus(int p, int l, int r, long long k)
{
	if (Tree[p].l >= l && Tree[p].r <= r)
	{
		Tree[p].sum = (Tree[p].sum + k * (Tree[p].r - Tree[p].l + 1)) % MOD;
		Tree[p].add = (Tree[p].add + k) % MOD;
		return;
	}
	int m = (Tree[p].l + Tree[p].r) >> 1;
	pushDown(p);
	if (l <= m)
		queryUpdatePlus(p << 1, l, r, k);
	if (r > m)
		queryUpdatePlus(p << 1 | 1, l, r, k);
	pushUp(p);
}

void queryUpdateMultiply(int p, int l, int r, long long k)
{
	if (Tree[p].l >= l && Tree[p].r <= r)
	{
		Tree[p].add = (k * Tree[p].add) % MOD;
		Tree[p].mul = (k * Tree[p].mul) % MOD;
		Tree[p].sum = (k * Tree[p].sum) % MOD;
		return;
	}
	int m = (Tree[p].l + Tree[p].r) >> 1;
	pushDown(p);
	if (l <= m)
		queryUpdateMultiply(p << 1, l, r, k);
	if (r > m)
		queryUpdateMultiply(p << 1 | 1, l, r, k);
	pushUp(p);
}

int main()
{
	int n = read(), m = read();
	read();
	vector<node>(n * 4 + 1).swap(Tree);
	vector<long long>(n + 1).swap(Val);
	for (int i = 1; i <= n; i++)
		Val[i] = read();

	Build(1, 1, n);

	long long tmp;
	for (int i = 1; i <= m; i++)
	{
		tmp = read();
		if (tmp == 1)
		{
			long long x = read(), y = read(), k = read();
			queryUpdateMultiply(1, x, y, k);
		}
		else if (tmp == 2)
		{
			long long x = read(), y = read(), k = read();
			queryUpdatePlus(1, x, y, k);
		}
		else
		{
			long long x = read(), y = read();
			printf("%lld\n", querySearch(1, x, y));
		}
	}
}