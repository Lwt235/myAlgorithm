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
#include <fstream>
#include <string.h>
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
        ans.sign = 1;
        int n = a.fractionPart.size(), m = b.fractionPart.size(), Min = min(n, m), Max = max(n, m);
        bool isNegative = false;
        if (n != 0 || m != 0) {
            vector<int>(Max, 0).swap(ans.fractionPart);
            //ans.fractionPart.resize(Max, 0);
            for (int i = 0; i < n - Min; i++)
                ans.fractionPart[i] += a.sign * a.fractionPart[i];
            for (int i = 0; i < m - Min; i++)
                ans.fractionPart[i] += b.sign * b.fractionPart[i];
            for (int i = 0; i < Min; i++)
                ans.fractionPart[i + Max - Min] += a.sign * a.fractionPart[n - Min + i] + b.sign * b.fractionPart[m - Min + i];

            for (int i = 0; i < Max - 1; i++)
                if (ans.fractionPart[i] >= 10) {
                    ans.fractionPart[i] -= 10;
                    ans.fractionPart[i + 1]++;
                }
                else if (ans.fractionPart[i] < 0) {
                    ans.fractionPart[i] += 10;
                    ans.fractionPart[i + 1]--;
                }
            
            if (ans.fractionPart.back() >= 10) {
                ans.fractionPart.back() -= 10;
                if (ans.integerPart.size() == 0) ans.integerPart.emplace_back(1);
                else ans.integerPart[0]++;
            }
            else if (ans.fractionPart.back() <= -10) {
                ans.fractionPart.back() += 10;
                if (ans.integerPart.size() == 0) ans.integerPart.emplace_back(-1);
                else ans.integerPart[0]--;
            }
            if (ans.fractionPart.back() < 0) {
                isNegative = true;
                for (int i = 0; i < Max; i++)
                    ans.fractionPart[i] = -ans.fractionPart[i];
                for (int i = 0; i < Max - 1; i++)
                    if (ans.fractionPart[i] < 0) {
                        ans.fractionPart[i] += 10;
                        ans.fractionPart[i + 1]--;
                    }
            }
            while (!ans.fractionPart.empty() && !ans.fractionPart[0])
                ans.fractionPart.erase(ans.fractionPart.begin());
        }

        n = a.integerPart.size(), m = b.integerPart.size(), Min = min(n, m), Max = max(n, m);
        ans.integerPart.resize(Max, 0);
        for (int i = 0; i < Min; i++)
            ans.integerPart[i] += a.sign * a.integerPart[i] + b.sign * b.integerPart[i];
        for (int i = Min; i < n; i++)
            ans.integerPart[i] += a.sign * a.integerPart[i];
        for (int i = Min; i < m; i++)
            ans.integerPart[i] += b.sign * b.integerPart[i];

        for (int i = 0; i < Max - 1; i++)
            if (ans.integerPart[i] >= 10) {
                ans.integerPart[i] -= 10;
                ans.integerPart[i + 1]++;
            }
            else if (ans.integerPart[i] < 0) {

                ans.integerPart[i] += 10;
                ans.integerPart[i + 1]--;
            }
        if (ans.integerPart.back() >= 10) {
            ans.integerPart.back() -= 10;
            ans.integerPart.emplace_back(1);
        }
        else if (ans.integerPart.back() < 0) {
            ans.sign = -1;
            for (int i = 0; i < Max; i++)
                ans.integerPart[i] = -ans.integerPart[i];
            for (int i = 0; i < Max - 1; i++)
                if (ans.integerPart[i] < 0) {
                    ans.integerPart[i] += 10;
                    ans.integerPart[i + 1]--;
                }
        }
        while (ans.integerPart.size() > 1 && !ans.integerPart.back()) ans.integerPart.pop_back();
        if (ans.fractionPart.empty())
            return ans;
        if (ans.sign == -1) {
            if (isNegative) {
                return ans;
            }
            else {
                ans.fractionPart[0] = 10 - ans.fractionPart[0];
                for (int i = 1; i < ans.fractionPart.size(); i++)
                    ans.fractionPart[i] = 9 - ans.fractionPart[i];
                vector<int>tmp = ans.fractionPart;
                ans.fractionPart = {};
                ans = ans + 1ll;
                ans.sign = -1;
                ans.fractionPart = tmp;
            }
        }
        else {
            if (isNegative) {
                if (ans.integerPart.size() == 1 && ans.integerPart[0] == 0) {
                    ans.sign = -1;
                    return ans;
                }
                ans.fractionPart[0] = 10 - ans.fractionPart[0];
                for (int i = 1; i < ans.fractionPart.size(); i++)
                    ans.fractionPart[i] = 9 - ans.fractionPart[i];
                vector<int>tmp = ans.fractionPart;
                ans.fractionPart = {};
                ans = ans - 1ll;
                ans.fractionPart = tmp;
            }
            else {
                return ans;
            }
        }
        return ans;
    }

public:
    BigNum(const string& number = "") {
        sign = 1;
        if (number.empty())
            return;
        if (number[0] == '-') {
            sign = -1;
        }
        stringstream ss(number);
        string tmp;
        vector<string>res;
        while (getline(ss, tmp, '.')) res.emplace_back(tmp);

        if (res.size() > 2 || (res.size() == 2 && res[1] == "")) throw 1;
        if (res.size() == 1) res.emplace_back("");
        if (res[0] == "") res[0] = "0";
        if (res[0][0] == '-') res[0].erase(res[0].begin());
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
    /*void show()
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
    }*/

    //重载运算符
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
    const BigNum operator - () const {
        BigNum res = *this;
        res.sign *= -1;
        return res;
    }
    const BigNum operator - (const BigNum& a) const {
        return addition(*this, -a);
    }
    BigNum& operator += (const BigNum& a) {
        *this = addition(*this, a);
        return *this;
    }
    friend inline ostream& operator <<(ostream& out, const BigNum& num);
};
inline ostream& operator << (ostream& out, const BigNum& num) {
    if (num.sign == -1) out << "-";
    for (int i = num.integerPart.size() - 1; i >= 0; i--)
        out << num.integerPart[i];
    if (num.fractionPart.empty()) {
        return out;
    }
    out << ".";
    for (int i = num.fractionPart.size() - 1; i >= 0; i--)
        out << num.fractionPart[i];
    return out;
}
int main()
{
    string num1;
    string num2;
    ifstream in("TestData.in");
    ofstream out("ResData.out");
    while (in >> num1 >> num2) {
        BigNum ans = num1;
        ans += num2;
        out << ans << endl;
        cout << ans << endl;
    }
}