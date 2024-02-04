#define _CRT_SECURE_NO_WARNINGS 1
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

class ACAutomaton {
private:
    char val;
    vector<int>exist;
    ACAutomaton* fail;
    vector<ACAutomaton*>childs;
    ACAutomaton* createNewNode(char val = '\0', vector<int>exist = {}, ACAutomaton* fail=nullptr, vector<ACAutomaton*>childs = {}) {
        return new ACAutomaton(val, exist, fail, childs);
    }
    int findPos(char val, ACAutomaton* node)
    {
        for (int i = 0; i < node->childs.size(); i++)
            if (val == node->childs[i]->val)
                return i;
        return -1;
    }
public:
    ACAutomaton(char Val = '\0', vector<int>Exist = {}, ACAutomaton* Fail = nullptr, vector<ACAutomaton*>Childs = {}) {
        val = Val;
        exist = Exist;
        fail = Fail;
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
                    childs[i]->exist.emplace_back(words.length());
                else
                    childs[i]->insert(words, start + 1);
                return;
            }
        ACAutomaton* frontNode = createNewNode(words[start]);
        if (start == words.length() - 1)
            frontNode->exist.emplace_back(words.length());
        childs.emplace_back(frontNode);
        if (start != words.length() - 1)
        {
            for (int i = start + 1; i < words.length() - 1; i++)
            {
                ACAutomaton* newNode = createNewNode(words[i]);
                frontNode->childs.emplace_back(newNode);
                frontNode = newNode;
            }
            frontNode->childs.emplace_back(createNewNode(words.back(), { (int)words.length() }));
        }
    }
    void updateFailPointer()
    {
        queue<ACAutomaton*>Qu;
        for (int i = 0; i < childs.size(); i++)
        {
            childs[i]->fail = this;
            Qu.emplace(childs[i]);
        }
        while (!Qu.empty())
        {
            ACAutomaton* selected = Qu.front(); Qu.pop();
            for (int i = 0; i < selected->childs.size(); i++)
            {
                ACAutomaton* fafail = selected->fail;
                int Pos = findPos(selected->childs[i]->val, fafail);
                while (fafail != nullptr && Pos == -1)
                {
                    fafail = fafail->fail;
                    if (fafail == nullptr) break;
                    Pos = findPos(selected->childs[i]->val, fafail);
                }
                if (fafail == nullptr)
                    selected->childs[i]->fail = this;
                else
                {
                    selected->childs[i]->fail = fafail->childs[Pos];
                    for (int k = 0; k < fafail->childs[Pos]->exist.size(); k++)
                        selected->childs[i]->exist.emplace_back(fafail->childs[Pos]->exist[k]);
                }
                Qu.emplace(selected->childs[i]);
            }
        }
    }
    vector<pair<int, int>>find(const string words, int start = 0)
    {
        ACAutomaton* cur = this;
        vector<pair<int, int>>res;
        for (int i = start; i < words.length(); i++)
        {
            int Pos = findPos(words[i], cur);
            while (Pos == -1 && cur->fail != nullptr)
            {
                cur = cur->fail;
                if (cur->fail == nullptr) break;
                Pos = findPos(words[i], cur);
            }
            if (Pos != -1)
                cur = cur->childs[Pos];
            else
                continue;
            if (!cur->exist.empty())
            {
                for (int j = 0; j < cur->exist.size(); j++)
                    res.emplace_back(i - cur->exist[j] + 1, i);
            }
        }
        return res;
    }
};

int main()
{
    ACAutomaton AC;
    int N = read();
    while (N--)
    {
        string str;
        cin >> str;
        AC.insert(str);
    }
    AC.updateFailPointer();
    string str;
    cin >> str;
    vector<pair<int, int>>res = AC.find(str);
    for (int i = 0; i < res.size(); i++)
        cout << res[i].first << " " << res[i].second << endl;
    return 0;
}