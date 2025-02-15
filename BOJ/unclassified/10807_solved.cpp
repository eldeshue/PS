
#include <iostream>

int buffer[100];

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, v, cnt = 0;
	std::cin >> N;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> buffer[i];
	}
	std::cin >> v;
	for (int i = 0; i < N; ++i)
	{
		if (buffer[i] == v)
		{
			cnt++;
		}
	}
	std::cout << cnt;
}