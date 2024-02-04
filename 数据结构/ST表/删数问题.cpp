#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
vector<int>lg2;
vector<int>N(1);
vector<vector<int>> build(const vector<int>& arr)
{
	int n = arr.size() - 1;
	vector<int>(n + 1).swap(lg2);
	lg2[1] = 0;
	for (int i = 2; i <= n; i++)
		lg2[i] = lg2[i >> 1] + 1;
	vector<vector<int>>ST(n + 1, vector<int>(lg2[n] + 1));
	for (int i = 1; i <= n; i++)
		ST[i][0] = arr[i];
	for (int j = 1; j <= lg2[n]; j++)
		for (int i = 1; i <= n - (1 << j) + 1; i++)
			ST[i][j] = min(ST[i][j - 1], ST[i + (1 << (j - 1))][j - 1]);
	return ST;
}
int search(int L, int R, vector<vector<int>>& ST)
{
	int Len = lg2[R - L + 1];
	return min(ST[L][Len], ST[R - (1 << Len) + 1][Len]);
}
int main()
{
	string str;
	int k;
	cin >> str;
	for (int i = 0; i < str.length(); i++)
		N.push_back(str[i] - '0');
	cin >> k;
	vector<vector<int>>ST = build(N);

	int Len = N.size() - 1;
	vector<vector<int>>last(Len + 1, vector<int>(10));
	for (int i = 0; i < 10; i++)
		last[Len][i] = Len + 1;
	last[Len][N[Len]] = Len;
	for (int i = Len - 1; i >= 1; i--)
	{
		for (int j = 0; j < 10; j++)
			if (N[i] == j)
				last[i][j] = i;
			else
				last[i][j] = last[i + 1][j];
	}
	bool flag = false;
	for (int i = 1; i <= Len; i++)
	{
		if (i + k > Len)
			break;
		int minn = search(i, i + k, ST);
		k -= last[i][minn] - i;
		i = last[i][minn];
		if (minn || flag)
		{
			cout << minn;
			flag = true;
		}
	}
	if (!flag) cout << 0;
}