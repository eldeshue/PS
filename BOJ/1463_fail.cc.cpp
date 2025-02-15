/*
#include <iostream>

int min = 1e9;

void divide(int n, int cnt)
{
	if (n == 1)
	{
		if (cnt < min)
		{
			min = cnt;
		}
		return;
	}

	if ((n % 3) == 0)
	{
		divide(n / 3, cnt + 1);
	}
	if ((n % 2) == 0)
	{
		divide(n / 2, cnt + 1);
	}
	divide(n - 1, cnt + 1);
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	int N;
	std::cin >> N;
	divide(N, 0);
	std::cout << min;
}
*/