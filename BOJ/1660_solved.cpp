/*
	01 배낭문제의 응용.

	01배낭 혹은 동전교환 문제의 응용임.
*/
#include <iostream>
#include <vector>
#include <memory.h>

std::vector<int> balls;	// 분할 불가능한 가치의 item, 직접 구해야함.
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
			if (ball < n)	// 해당 아이템을 넣을지 말지에 대해서 dp
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
		if (sum > N)	// 아이템 찾기
			break;
		cache[sum] = 1;	// 아이템 세팅
		balls.push_back(sum);
		sum = sum * (n + 3) / n;
		n++;
	}
	std::cout << DP(N);
}
