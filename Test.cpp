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
#include <cmath>
#include <sstream>
#define MOD 1000000007
#define INF 2000000000
using namespace std;
inline long long read() {
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
class BigNum {
    int sign;
    vector<int>integerPart;
    vector<int>fractionPart;
    
    //-1:a<b 0:a=b 1:a>b
    int bigNumCompare(const BigNum& a, const BigNum& b) const {
        int base = 1;

        //处理负数情况
        if (a.sign == -1 && b.sign == -1) base = -1;
        else if (a.sign == -1) return -base;
        else if (b.sign == -1) return base;

        if (a.integerPart.size() < b.integerPart.size()) return -base;
        else if (a.integerPart.size() > b.integerPart.size()) return base;
        int cur = a.integerPart.size() - 1;
        while (cur--) {
            if (a.integerPart[cur] < b.integerPart[cur]) return -base;
            else if (a.integerPart[cur] > b.integerPart[cur]) return base;
        }
        return 0;
    }

    BigNum addition(const BigNum& a, const BigNum& b) const {
        BigNum ans;
        int n = a.fractionPart.size(), m = b.fractionPart.size(), Min = min(n, m), Max = max(n, m);
        if (n != 0 || m != 0) {
            ans.fractionPart.resize(Max, 0);
            for (int i = 0; i < n - Min; i++)
                ans.fractionPart[i] += a.fractionPart[i];
            for (int i = 0; i < m - Min; i++)
                ans.fractionPart[i] += b.fractionPart[i];
            for (int i = 0; i < Min; i++)
                ans.fractionPart[i + Max - Min] += a.fractionPart[n - Min + i] + b.fractionPart[m - Min + i];

            for (int i = 0; i < Max - 1; i++)
                if (ans.fractionPart[i] >= 10) {
                    ans.fractionPart[i] -= 10;
                    ans.fractionPart[i + 1]++;
                }
            if (ans.fractionPart.back() >= 10) {
                ans.fractionPart.back() -= 10;
                if (ans.integerPart.size() == 0) ans.integerPart.emplace_back(1);
                else ans.integerPart[0]++;
            }
            while (!ans.fractionPart.empty() && !ans.fractionPart[0])
                ans.fractionPart.erase(ans.fractionPart.begin());
        }

        n = a.integerPart.size(), m = b.integerPart.size(), Min = min(n, m), Max = max(n, m);
        ans.integerPart.resize(Max, 0);
        for (int i = 0; i < Min; i++)
            ans.integerPart[i] += a.integerPart[i] + b.integerPart[i];
        for (int i = Min; i < n; i++)
            ans.integerPart[i] += a.integerPart[i];
        for (int i = Min; i < m; i++)
            ans.integerPart[i] += b.integerPart[i];

        for (int i = 0; i < Max - 1; i++)
            if (ans.integerPart[i] >= 10) {
                ans.integerPart[i] -= 10;
                ans.integerPart[i + 1]++;
            }
        if (ans.integerPart.back() >= 10) {
            ans.integerPart.back() -= 10;
            ans.integerPart.emplace_back(1);
        }
        return ans;
    }

public:
    BigNum(const string& number = "") {
        sign = 1;
        if (number.empty())
            return;
        string num = number + '.';
        if (num[0] == '-') {
            sign = -1;
            num.erase(num.begin());
        }
        stringstream ss(num);
        string tmp;
        vector<string>res;
        while (getline(ss, tmp, '.')) res.emplace_back(tmp);

        if (res.size() > 2) throw -1;
        if (res.size() == 1) res.emplace_back("");
        string strInt = res[0], strFrac = res[1];

        int intLen = strInt.length(), fracLen = strFrac.length();
        vector<int>(intLen).swap(integerPart);
        vector<int>(fracLen).swap(fractionPart);
        for (int i = 0; i < intLen; i++)
            integerPart[intLen - i - 1] = strInt[i] - '0';
        for (int i = 0; i < fracLen; i++)
            fractionPart[fracLen - i - 1] = strFrac[i] - '0';
    }
    BigNum(const long long& number) {
        sign = number < 0 ? -1 : 1;
        long long num = sign * number;
        while (num) {
            integerPart.emplace_back(num % 10);
            num /= 10;
        }
    }
    /*template<typename T>
    BigNum(T& number) {
        isNegative = number < 0;
        T num = isNegative ? -number : number;
        long long intPart = (long long)num;
        T fracPart = num - intPart * 1.0L;
        while (intPart) {
            integerPart.emplace_back(intPart % 10);
            intPart /= 10;
        }
        while (fracPart >= 1e-20L) {
            fractionPart.emplace(fractionPart.begin(), (int)fracPart);
            fracPart = fracPart * (10.0L) - (int)(fracPart * 10.0L);
        }
    }*/
    BigNum(const long double& number) {
        sign = number < 0 ? -1 : 1;
        long double num = sign * number;
        long long intPart = (long long)num;
        long double fracPart = num - intPart * 1.0L;
        while (intPart) {
            integerPart.emplace_back(intPart % 10);
            intPart /= 10;
        }
        int cur = 20;//最大提取位数
        while (fracPart >= 1e-20L && cur--) {
            fractionPart.emplace(fractionPart.begin(), (int)(fracPart * 10));
            fracPart = fracPart * (10.0L) - (int)(fracPart * 10.0L);
        }
    }
    BigNum(const double& number) {
        sign = number < 0 ? -1 : 1;
        double num = sign * number;
        long long intPart = (long long)num;
        double fracPart = num - intPart * 1.0;
        while (intPart) {
            integerPart.emplace_back(intPart % 10);
            intPart /= 10;
        }
        int cur = 20;//最大提取位数
        while (fracPart >= 1e-20 && cur--) {
            fractionPart.emplace(fractionPart.begin(), (int)(fracPart * 10));
            fracPart = fracPart * (10.0) - (int)(fracPart * 10.0);
        }
    }
    void show()
    {
        if (sign == -1) printf("-");
        for (int i = integerPart.size() - 1; i >= 0; i--)
            printf("%d", integerPart[i]);
        if (fractionPart.empty()) {
            printf("\n");
            return;
        }
        printf(".");
        for (int i = fractionPart.size() - 1; i >= 0; i--)
            printf("%d", fractionPart[i]);
        printf("\n");
        return;
    }
    /*BigNum& operator = (const long long int& number) {
        isNegative = number < 0;
        long long num;
        num = number < 0 ? -number : number;
        vector<int>().swap(integerPart);
        while (num) {
            integerPart.emplace_back(num % 10);
            num /= 10;
        }
        return *this;
    }*/

    /*const BigNum operator + (const long long int& a) const {
        BigNum tmp = a;
        return plus(*this, tmp);
    }*/
    bool operator <(const BigNum& a) const { return bigNumCompare(*this, a) < 0; }
    bool operator >(const BigNum& a) const { return bigNumCompare(*this, a) > 0; }
    bool operator <=(const BigNum& a) const { return bigNumCompare(*this, a) <= 0; }
    bool operator >=(const BigNum& a) const { return bigNumCompare(*this, a) >= 0; }
    bool operator ==(const BigNum& a) const { return bigNumCompare(*this, a) == 0; }
    bool operator !=(const BigNum& a) const { return bigNumCompare(*this, a) != 0; }
    const BigNum operator + (const BigNum& a) const {
        return addition(*this, a);
    }
    BigNum& operator += (const BigNum& a) {
        *this = addition(*this, a);
        return *this;
    }

};
int main()
{
    string num1;
    string num2;
    while (cin >> num1 >> num2) {
        BigNum ans = num1;
        ans += num2;
        ans.show();
    }
}