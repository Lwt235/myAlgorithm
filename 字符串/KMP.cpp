#include <iostream>
#include <vector>
using namespace std;
vector <int> str_next;
string str1, str2;
void Build(string str)
{
	int i = 1, maxLength = 0;
	str_next.push_back(0);
	while (i < str.length())
	{
		if (str[maxLength] == str[i])
		{
			maxLength++;
			str_next.push_back(maxLength);
			i++;
		}
		else
		{
			if (maxLength == 0)
			{
				str_next.push_back(maxLength);
				i++;
			}
			else
				maxLength = str_next[maxLength - 1];
		}
	}
}
int Kmp(string str1, string str2)
{
	Build(str2);
	int Len = str1.length();
	int i = 0, j = 0;
	while (i < Len)
	{
		if (str1[i] == str2[j])
		{
			i++;
			j++;
		}
		else if (j > 0)
			j = str_next[j - 1];
		else
			i++;
		if (j == str2.length())
			return i - j;
	}
	return -1;
}
int main()
{
	cin >> str1 >> str2;
	cout << Kmp(str1, str2);
}