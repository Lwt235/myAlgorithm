#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
vector<int>lg2(500010);
vector<int>N(1);
vector<vector<int>>ST;
void build()
{
	int n = N.size() - 1;
	for (int i = 1; i <= n; i++)
		ST[i][0] = N[i];
	for (int j = 1; j <= lg2[n]; j++)
		for (int i = 1; i <= n - (1 << j) + 1; i++)
			ST[i][j] = min(ST[i][j - 1], ST[i + (1 << (j - 1))][j - 1]);
}
int search(int L, int R)
{
	int Len = lg2[R - L + 1];
	return min(ST[L][Len], ST[R - (1 << Len) + 1][Len]);
}
int main()
{
	string str;
	int k, T;
	lg2[1] = 0;
	for (int i = 2; i <= 500010; i++)
		lg2[i] = lg2[i >> 1] + 1;
	cin >> T;
	while (T--)
	{
		cin >> str;
		vector<int>(1).swap(N);
		for (int i = 0; i < str.length(); i++)
			N.push_back(str[i] - '0');
		cin >> k;
		if (str.length() == k)
		{
			cout << "0" << endl;
			continue;
		}
		int Len = N.size() - 1;
		vector<vector<int>>(Len + 1, vector<int>(lg2[Len] + 1)).swap(ST);
		build();

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
			int minn = search(i, i + k);
			k -= last[i][minn] - i;
			i = last[i][minn];
			if (minn || flag)
			{
				cout << minn;
				flag = true;
			}
		}
		if (!flag) cout << 0;
		cout << endl;
	}
}