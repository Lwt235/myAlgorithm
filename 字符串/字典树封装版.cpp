#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <set>
#include <map>
#include <cstring>
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
class Trie {
private:
	char val;
	bool isEnd;
	vector<Trie*>childs;
	Trie* createNewNode(int val = '\0', bool isEnd = false, vector<Trie*>childs = {}) {	
		return new Trie(val, isEnd, childs);
	}
public:
	Trie(int Val = '\0', bool IsEnd = false, vector<Trie*>Childs = {}) {
		val = Val;
		isEnd = IsEnd;
		childs = Childs;
	}
	void insert(const string words, int start = 0)
	{
		if (start >= words.length())
			return;
		for (int i = 0; i < childs.size(); i++)
			if (childs[i]->val == words[start])
			{
				if (start == words.length() - 1)
					childs[i]->isEnd = true;
				else
					childs[i]->insert(words, start + 1);
				return;
			}
		Trie* frontNode = createNewNode(words[start]);
		if (start == words.length() - 1)
			frontNode->isEnd = true;
		childs.emplace_back(frontNode);
		if (start != words.length() - 1)
		{
			for (int i = start + 1; i < words.length() - 1; i++)
			{
				Trie* newNode = createNewNode(words[i]);
				frontNode->childs.emplace_back(newNode);
				frontNode = newNode;
			}
			frontNode->childs.emplace_back(createNewNode(words.back(), true));
		}
	}
	bool find(const string words, int start = 0)
	{
		for (int i = 0; i < childs.size(); i++)
			if (childs[i]->val == words[start])
			{
				if (start == words.length() - 1)
					if (childs[i]->isEnd)
						return true;
					else
						return false;
				else
					return childs[i]->find(words, start + 1);
			}
		return false;
	}
};

int main()
{
	Trie dictionary;
	int n = read(), m = read();
	while (n--)
	{
		string tmp;
		cin >> tmp;
		dictionary.insert(tmp);
	}
	while (m--)
	{
		string tmp;
		cin >> tmp;
		if (dictionary.find(tmp))
			cout << "Find!\n";
		else
			cout << "Not find!\n";
	}
	return 0;
}