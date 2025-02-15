
#include <iostream>
#include <vector>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, M, K; // set M person among k position
	std::cin >> N >> M >> K;
	std::vector<int> pos(K);
	std::vector<int> result(K, 0);
	for (int i = 0; i < K; ++i)
		std::cin >> pos[i];

	auto isOk = [&](const int mid) -> bool
	{
		// lexiographicall max, pick front first
		result[0] = 1;
		int setCnt = 1, lastSetPos = pos[0];
		for (int i = 1; i < K; ++i)
		{
			if (pos[i] - lastSetPos >= mid)
			{
				setCnt++;
				if (setCnt <= M)
					result[i] = 1;
				else
					result[i] = 0;
				lastSetPos = pos[i];
			}
			else
			{
				result[i] = 0;
			}
		}
		return setCnt >= M;
	};

	// parametric search
	// range, half open, (]
	int left = 0, right = N;
	while (left < right)
	{
		int mid = (left + right + 1) >> 1;
		if (isOk(mid))
		{
			left = mid;
		}
		else
		{
			right = mid - 1;
		}
	}
	// print result
	isOk(right);
	for (const int &n : result)
	{
		std::cout << n;
	}
}
