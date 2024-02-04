#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
using namespace std;

void ZeroOnePack(vector<int>& Bag, int Weight, int Value)
{
    for (int j = Bag.size() - 1; j >= Weight; j--)
        Bag[j] = max(Bag[j], Bag[j - Weight] + Value);
    return;
}

void CompletePack(vector<int>& Bag, int Weight, int Value)
{
    for (int j = Weight; j < Bag.size(); j++)
        Bag[j] = max(Bag[j], Bag[j - Weight] + Value);
    return;
}

void MultiplePack(vector<int>& Bag, int Weight, int Value, int Amount)
{
    if (Amount * Weight >= Bag.size() - 1)
    {
        CompletePack(Bag, Weight, Value);
        return;
    }
    for (int k = 1; k <= Amount; k <<= 1)
    {
        ZeroOnePack(Bag, Weight * k, Value * k);
        Amount -= k;
    }
    ZeroOnePack(Bag, Weight * Amount, Value * Amount);
    return;
}

int main()
{
    int Tsh, Tsm, Teh, Tem, n;
    scanf("%d:%d %d:%d %d", &Tsh, &Tsm, &Teh, &Tem, &n);
    int V = (Teh - Tsh) * 60 + Tem - Tsm;
    vector<int>dp(V + 1);
    int T, C, P;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d %d %d", &T, &C, &P);
        if (P == 0)
            CompletePack(dp, T, C);
        else
            MultiplePack(dp, T, C, P);
    }
    printf("%d", dp[V]);
}