
#include <iostream>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int x, n;
	std::cin >> x;
	for (n = 1; n < x; ++n)
	{
		x -= n;
	}
	// n�� ¦���� ������, Ȧ���� �����
	if (n & 1)	// Ȧ��
	{
		std::cout << n + 1 - x << '/' << x;
	}
	else // ¦��
	{
		std::cout << x << '/' << n + 1 - x;
	}
}