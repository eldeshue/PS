/*
	01 �賶������ ����.

	01�賶 Ȥ�� ������ȯ ������ ������.
*/
#include <iostream>
#include <vector>
#include <memory.h>

std::vector<int> balls;	// ���� �Ұ����� ��ġ�� item, ���� ���ؾ���.
int cache[300001];

int DP(int n)
{
	if (cache[n] != -1)
	{
		return cache[n];
	}
	else
	{
		int temp = 2147483647;
		for (const int& ball :balls)
		{
			if (ball < n)	// �ش� �������� ������ ������ ���ؼ� dp
				temp = std::min(temp, DP(n - ball) + 1);
			else
				break;
		}
		return cache[n] = temp;
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(cache, -1, sizeof(cache));

	int N, n = 1, sum = 1;
	std::cin >> N;
	while (true)
	{
		if (sum > N)	// ������ ã��
			break;
		cache[sum] = 1;	// ������ ����
		balls.push_back(sum);
		sum = sum * (n + 3) / n;
		n++;
	}
	std::cout << DP(N);
}
