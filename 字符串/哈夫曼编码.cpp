#include <iostream>
#include <vector>
using namespace std;
struct Tree {
	char Value;
	int Frequency;
	int leftChild;
	int rightChild;
	int Parent;
	Tree() : Value('\0'), Frequency(2), leftChild(-1), rightChild(-1), Parent(-1) {};
	Tree(char Value, int Frequency) : Value(Value), Frequency(Frequency), leftChild(-1), rightChild(-1), Parent(-1) {};
	Tree(char Value, int Frequency, int leftChild, int rightChild, int Parent) : Value(Value), Frequency(Frequency), leftChild(leftChild), rightChild(rightChild), Parent(Parent) {};
}Huffman[101];
void Path(int Node, string path)
{
	if (Huffman[Node].leftChild == -1 && Huffman[Node].rightChild == -1)
		cout << Huffman[Node].Value << ":" << path << endl;
	else
	{
		if (Huffman[Node].leftChild != -1)
			Path(Huffman[Node].leftChild, path + "0");
		if (Huffman[Node].rightChild != -1)
			Path(Huffman[Node].rightChild, path + "1");
	}
}
int N, Len, sum;
int main()
{
	cin >> N;
	Len = N;
	for (int i = 1; i <= N; i++)
	{
		char tValue;
		double tFrequency;
		cin >> tValue >> tFrequency;
		Huffman[i]=Tree(tValue, int(tFrequency * 100));
	}
	while (Len > 1)
	{
		int X1 = -1, X2 = -1, M1 = 0x7fffffff, M2 = 0x7fffffff;
		for (int i = 1; i <= N + sum; i++)
			if (Huffman[i].Parent == -1)
			{
				if (Huffman[i].Frequency < M1)
				{
					M2 = M1;
					M1 = Huffman[i].Frequency;
					X2 = X1;
					X1 = i;
				}
				else if (Huffman[i].Frequency < M2)
				{
					X2 = i;
					M2 = Huffman[i].Frequency;
				}
			}
		sum++;
		Len--;
		Huffman[X1].Parent = N + sum;
		Huffman[X2].Parent = N + sum;
		Huffman[N + sum] = Tree('\0', Huffman[X1].Frequency + Huffman[X2].Frequency, X1, X2, -1);
	}
	Path(N + sum, "");
}