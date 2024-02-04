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
    BigNum multiplication(const BigNum& a, const BigNum& b) const {
        BigNum ans;
        ans.sign = a.sign * b.sign;
        vector<int>aFull = a.fractionPart, bFull = b.fractionPart;
        for (int i = 0; i < a.integerPart.size(); i++)
            aFull.emplace_back(a.integerPart[i]);
        for (int i = 0; i < b.integerPart.size(); i++)
            bFull.emplace_back(b.integerPart[i]);
        vector<int>res(aFull.size() + bFull.size());
        for (int i = 0; i < aFull.size(); i++)
            for (int j = 0; j < bFull.size(); j++)
                res[i + j] += aFull[i] * bFull[j];
        for (int i = 0; i < res.size() - 1; i++)
            if (res[i] >= 10) {
                res[i + 1] += res[i] / 10;
                res[i] %= 10;
            }
        for (int i = 0; i < a.fractionPart.size() + b.fractionPart.size(); i++)
            ans.fractionPart.emplace_back(res[i]);
        for (int i = a.fractionPart.size() + b.fractionPart.size(); i < res.size(); i++)
            ans.integerPart.emplace_back(res[i]);
        while (ans.integerPart.size() > 1 && !ans.integerPart.back()) ans.integerPart.pop_back();
        return ans;
    }

public:
    //针对各类型的构造函数
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

    //重载运算符
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
    BigNum& operator -= (const BigNum& a) {
        *this = addition(*this, -a);
        return *this;
    }
    const BigNum operator * (const BigNum& a) const {
        return multiplication(*this, a);
    }
    BigNum& operator *= (const BigNum& a) {
        *this = multiplication(*this, a);
        return *this;
    }
    friend inline ostream& operator <<(ostream& out, const BigNum& num);
    friend inline istream& operator >>(istream& in, BigNum& num);
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
inline istream& operator >> (istream& in, BigNum& num) {
    string str;
    in >> str;
    num = BigNum(str);
    return in;
}
int main()
{
    BigNum num1, num2;
    ifstream in("TestData.in");
    ofstream out("ResData.out");
    while (in >> num1 >> num2) {
        BigNum ans = num1 * num2;
        out << ans << endl;
        //cout << ans << endl;
    }
}