
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
	// ���� ����� Ÿ���� �߽��� ȹ��, �űⰡ a.
	// a���� ������ �Ÿ� ��ŭ ������.
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