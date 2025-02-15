
#include <iostream>
#include <memory.h>

int N, R1, C1, R2, C2;

int getDistFromCenter(int r, int c)
{
	r %= (2 * N - 1);
	c %= (2 * N - 1);
	return std::abs(N - 1 - r) + std::abs(N - 1 - c);
}

char getAscii(int r, int c)
{
	// 가장 가까운 타일의 중심을 획득, 거기가 a.
	// a에서 떨어진 거리 만큼 증가함.
	char result = 'a';
	int d = getDistFromCenter(r, c);
	if (d < N)
		result += d % 26;
	else
		result = '.';
	return result;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> N >> R1 >> C1 >> R2 >> C2;
	for (int row = R1; row <= R2; ++row)
	{
		for (int col = C1; col <= C2; ++col)
		{
			std::cout << getAscii(row, col);
		}
		std::cout << '\n';
	}
}