/*
#include <iostream>
#include <cmath>

int numName, width;
int names[1000];
int*** cache; // ��ǥ�� = f( ���� ��, ���� �̸� )

int DP(int curRow, int curLength, int curPos)
{
	// base case
	if (curPos == numName - 1)
	{
		return 0;
	}

	int& tgt = cache[curRow][curLength][curPos];
	// cache hit
	if (tgt != -1)
	{
		return tgt;
	}
	// cache miss
	else
	{
		int nextLength = curLength + 1 + names[curPos];
		int go = 1000000, stay = 1000000;
		if (curLength != 0)
		{	// ���ٲ�, ���� �ٲٸ� ������ ó���� �ϳ��� ����.
			go = std::pow(width - curLength, 2) + DP(curRow + 1, names[curPos], curPos + 1);
		}
		if (nextLength <= width)
		{	// �� �ȹٲ�
			stay = DP(curRow, nextLength, curPos + 1);
		}

		return tgt = std::min(go, stay);
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	
	std::cin >> numName >> width;
	cache = new int** [numName + 1]; 
	for (int i = 0; i <= numName; ++i)
	{
		cache[i] = new int* [width + 1];
		for (int j = 0; j <= width; ++j)
		{
			cache[i][j] = new int[numName + 1];
			for (int k = 0; k <= numName; ++k)
			{
				cache[i][j][k] = -1;
			}
		}
	}

	for (int i = 0; i < numName; ++i)
	{
		std::cin >> names[i];
	}
	
	std::cout << DP(0, names[0], 1); // ù move���� ������.
}
*/
