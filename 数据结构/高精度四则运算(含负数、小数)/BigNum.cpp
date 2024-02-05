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
    string maxInf = "999999999999999.99";

    //-1:a<b 0:a=b 1:a>b
    int bigNumCompare(const BigNum& a, const BigNum& b) const {
        int base = 1;

        //特判+0,-0
        if (a.integerPart.size() == 1 && a.fractionPart.empty() && b.integerPart.size() == 1 && b.fractionPart.empty() && a.integerPart[0] == 0 && b.integerPart[0] == 0) return 0;

        //处理负数情况
        if (a.sign == -1 && b.sign == -1) base = -1;
        else if (a.sign == -1) return -base;
        else if (b.sign == -1) return base;

        //先比整数
        if (a.integerPart.size() < b.integerPart.size()) return -base;
        else if (a.integerPart.size() > b.integerPart.size()) return base;
        int cur = a.integerPart.size() - 1;
        while (cur >= 0) {
            if (a.integerPart[cur] < b.integerPart[cur]) return -base;
            else if (a.integerPart[cur] > b.integerPart[cur]) return base;
            cur--;
        }

        //再比小数
        for (int aT = a.fractionPart.size() - 1, bT = b.fractionPart.size() - 1; aT >= 0 && bT >= 0; aT--, bT--) {
            if (a.fractionPart[aT] < b.fractionPart[bT]) return -base;
            else if (a.fractionPart[aT] > b.fractionPart[bT]) return base;
        }
        if (a.fractionPart.size() == b.fractionPart.size()) return 0;
        else return (a.fractionPart.size() < b.fractionPart.size() ? -1 : 1) * base;
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
    BigNum devision(const BigNum& a, const long long& b) const {
        if (b == 0) return BigNum(maxInf);
        BigNum ans, aFull;
        ans.sign = a.sign * (b < 0 ? -1 : 1);
        long long B = abs(b);
        aFull.integerPart = a.fractionPart;
        long long base = a.fractionPart.size();
        for (int i = 0; i < a.integerPart.size(); i++)
            aFull.integerPart.emplace_back(a.integerPart[i]);
        while (!aFull.integerPart.empty() && !aFull.integerPart.back()) aFull.integerPart.pop_back();
        long long x = 0;
        for (int i = aFull.integerPart.size() - 1; i >= 0; i--) {
            ans.integerPart.emplace(ans.integerPart.begin(), (aFull.integerPart[i] + x * 10) / B);
            x = (aFull.integerPart[i] + x * 10) % B;
        }
        while (!ans.integerPart.empty() && !ans.integerPart.back()) ans.integerPart.pop_back();
        int maxAccuracy = 16 - base;
        while (x && maxAccuracy >= 0) {
            ans.fractionPart.emplace(ans.fractionPart.begin(), (x * 10) / B);
            x = (x * 10) % B;
            maxAccuracy--;
        }
        for (int i = 0; i < base; i++) {
            if (ans.integerPart.empty()) {
                ans.fractionPart.emplace_back(0);
                continue;
            }
            ans.fractionPart.emplace_back(ans.integerPart.front());
            ans.integerPart.erase(ans.integerPart.begin());
        }
        if (ans.integerPart.empty()) ans.integerPart.emplace_back(0);
        while (ans.fractionPart.size() > 18) ans.fractionPart.erase(ans.fractionPart.begin());
        if (ans.fractionPart.size() == 18) {
            if (ans.fractionPart[0] >= 5) {
                ans.fractionPart[1]++;
                int cur = 0;
                while (cur < ans.fractionPart.size() && ans.fractionPart[cur] >= 10) {
                    ans.fractionPart[cur] -= 10;
                    ans.fractionPart[++cur]++;
                }
                if (ans.fractionPart.back() >= 10) {
                    ans.fractionPart.back() -= 10;
                    ans += 1;
                }
            }
            ans.fractionPart.erase(ans.fractionPart.begin());
        }
        while (!ans.fractionPart.empty() && !ans.fractionPart[0]) ans.fractionPart.erase(ans.fractionPart.begin());
        return ans;
    }
    BigNum devision(const BigNum& a, const BigNum& b) const {
        if (b == 0) return BigNum(maxInf);
        BigNum ans, aFull, bFull;
        ans.sign = a.sign * b.sign;
        aFull.integerPart = a.fractionPart, bFull.integerPart = b.fractionPart;
        while (aFull.integerPart.size() < bFull.integerPart.size()) aFull.integerPart.emplace(aFull.integerPart.begin(), 0);
        while (aFull.integerPart.size() > bFull.integerPart.size()) bFull.integerPart.emplace(bFull.integerPart.begin(), 0);
        for (int i = 0; i < a.integerPart.size(); i++)
            aFull.integerPart.emplace_back(a.integerPart[i]);
        for (int i = 0; i < b.integerPart.size(); i++)
            bFull.integerPart.emplace_back(b.integerPart[i]);
        while (!aFull.integerPart.empty() && !aFull.integerPart.back()) aFull.integerPart.pop_back();
        while (!bFull.integerPart.empty() && !bFull.integerPart.back()) bFull.integerPart.pop_back();

        if (aFull < bFull)
            ans.integerPart = { 0 };
        else if (aFull == bFull) {
            ans.integerPart = { 1 };
            return ans;
        }
        int Len = 0;
        while (aFull > bFull) {
            bFull.integerPart.emplace(bFull.integerPart.begin(), 0);
            Len++;
        }
        Len--;
        if (Len >= 0)
            bFull.integerPart.erase(bFull.integerPart.begin());
        while (Len >= 0) {
            ans.integerPart.emplace(ans.integerPart.begin(), 0);
            while (aFull >= bFull) {
                aFull -= bFull;
                ans.integerPart[0]++;
            }
            Len--;
            if (Len < 0) break;
            bFull.integerPart.erase(bFull.integerPart.begin());
        }
        int maxAccuracy = 16;
        while ((aFull.integerPart.size() > 1 || aFull.integerPart[0] != 0) && maxAccuracy >= 0) {
            aFull.integerPart.emplace(aFull.integerPart.begin(), 0);
            ans.fractionPart.emplace(ans.fractionPart.begin(), 0);
            while (aFull >= bFull) {
                aFull -= bFull;
                ans.fractionPart[0]++;
            }
            maxAccuracy--;
        }
        if (maxAccuracy < 0) {
            if (ans.fractionPart[0] >= 5)
                ans.fractionPart[1]++;
            ans.fractionPart.erase(ans.fractionPart.begin());

            int cur = 0;
            while (cur < ans.fractionPart.size() && ans.fractionPart[cur] >= 10) {
                ans.fractionPart[cur] -= 10;
                ans.fractionPart[++cur]++;
            }
            if (ans.fractionPart.back() >= 10) {
                ans.fractionPart.back() -= 10;
                ans += 1;
            }
        }
        while (!ans.fractionPart.empty() && !ans.fractionPart[0]) ans.fractionPart.erase(ans.fractionPart.begin());
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
        while (!integerPart.size() > 1 && !integerPart.back()) integerPart.pop_back();
        while (!fractionPart.empty() && !fractionPart[0]) fractionPart.erase(fractionPart.begin());
    }
    BigNum(const int& number) {
        sign = number < 0 ? -1 : 1;
        int num = sign * number;
        if (num == 0) integerPart.emplace_back(0);
        while (num) {
            integerPart.emplace_back(num % 10);
            num /= 10;
        }
    }
    BigNum(const long& number) {
        sign = number < 0 ? -1 : 1;
        long num = sign * number;
        if (num == 0) integerPart.emplace_back(0);
        while (num) {
            integerPart.emplace_back(num % 10);
            num /= 10;
        }
    }
    BigNum(const long long& number) {
        sign = number < 0 ? -1 : 1;
        long long num = sign * number;
        if (num == 0) integerPart.emplace_back(0);
        while (num) {
            integerPart.emplace_back(num % 10);
            num /= 10;
        }
    }
    BigNum(const float& number) {
        sign = number < 0 ? -1 : 1;
        float num = sign * number;
        long long intPart = (long long)num;
        if (intPart == 0) integerPart.emplace_back(0);
        float fracPart = num - intPart * 1.0;
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
    BigNum(const double& number) {
        sign = number < 0 ? -1 : 1;
        double num = sign * number;
        long long intPart = (long long)num;
        if (intPart == 0) integerPart.emplace_back(0);
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
    BigNum(const long double& number) {
        sign = number < 0 ? -1 : 1;
        long double num = sign * number;
        long long intPart = (long long)num;
        if (intPart == 0) integerPart.emplace_back(0);
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
    const BigNum operator * (const BigNum& a) const {
        return multiplication(*this, a);
    }
    const BigNum operator / (const long long& a) const {
        return devision(*this, a);
    }
    const BigNum operator / (const BigNum& a) const {
        return devision(*this, a);
    }
    BigNum& operator += (const BigNum& a) {
        *this = addition(*this, a);
        return *this;
    }
    BigNum& operator -= (const BigNum& a) {
        *this = addition(*this, -a);
        return *this;
    }
    BigNum& operator *= (const BigNum& a) {
        *this = multiplication(*this, a);
        return *this;
    }
    BigNum& operator /= (const long long& a) {
        *this = devision(*this, a);
        return *this;
    }
    BigNum& operator /= (const BigNum& a) {
        *this = devision(*this, a);
        return *this;
    }
    friend inline ostream& operator <<(ostream& out, const BigNum& num);
    friend inline istream& operator >>(istream& in, BigNum& num);

    //设定无穷大的值(string类,使用十进制)
    void setInf(string val) {
        maxInf = val;
    }
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
    //ifstream in("TestData.in");
    //ofstream out("ResData.out");
    while (cin >> num1 >> num2) {
        BigNum ans = num1 / num2;
        cout << ans << endl;
        //cout << ans << endl;
    }
}