#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include <cstdio>
#include <iomanip>
#include <Windows.h>
#include <ctime>
using namespace std;
long long base[16] = { 10,100,1000,10000,100000,1000000,10000000,100000000,1000000000,10000000000,100000000000,1000000000000,10000000000000,100000000000000,1000000000000000,10000000000000000 };
void SetColorAndBackground(int ForgC = 7, int BackC = 0) {
	WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
}
int main()
{
	ofstream testfile("TestData.in"), resfile("TestData.out");
	int T;
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<>dist(0, 15);
	cout << "输入测试数据组数：" << endl;
	cin >> T;
	//生成测试数据
	while (T--) {
		int intLen = dist(gen), fracLen = dist(gen);
		uniform_int_distribution<>sgn(0, 1);
		uniform_int_distribution<long long>Intdist(0, base[intLen] - 1), Fracdist(0, base[fracLen] - 1);
		long double testData0 = (Intdist(gen) + Fracdist(gen) * 1.0L / base[fracLen]) * (sgn(gen) ? 1.0L : -1.0L);
		long double testData1 = (Intdist(gen) + Fracdist(gen) * 1.0L / base[fracLen]) * (sgn(gen) ? 1.0L : -1.0L);
		testfile << fixed << setprecision(16) << testData0 << " " << testData1 << endl;
		resfile << fixed << setprecision(16) << testData0 * testData1 << endl;
		printf("%33.16Lf + %33.16Lf = %34.16Lf\n", testData0, testData1, testData0 * testData1);
	}
	cout << "数据生成完成，执行测试程序:" << endl;
	double startTime = clock();
	system("BigNum.exe");
	double endTime = clock();
	ifstream ansFile("TestData.out"), checkFile("ResData.out");
	long double a, b;
	long double maxDifference = 0;
	int tag = 1;
	while (ansFile >> a && checkFile >> b) {
		maxDifference = max(maxDifference, fabsl(a - b));
		cout << "No." << tag++ << ": ";
		if (fabsl(a - b) <= 1.0L)
			cout << fixed << setprecision(16) << "Correct\tAbsoluteDifference: " << fabsl(a - b) << endl;
		else {
			SetColorAndBackground(4, 0);
			cout << fixed << setprecision(16) << "WrongAnswer: Find \"" << b << "\"but the answer is \"" << a << "\"" << endl;
			SetColorAndBackground();
			system("pause");
			return 0;
		}
	}
	SetColorAndBackground(10, 0);
	cout << "Accepted! maxDifference: " << maxDifference;
	cout << " time:" << endTime - startTime << "ms" << endl;
	SetColorAndBackground();
	system("pause");
}