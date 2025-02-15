
#include <iostream>
#include <vector>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	// input
	int W, N;
	std::cin >> W >> N;
	std::vector<int> A(N + 1);
	std::vector<std::pair<int, int>> cache(W, {-1, -1});
	for (int i = 0; i < N; ++i)
		std::cin >> A[i];
	// meet in the middle
	// set cache
	for (int i = 0; i < N - 1; ++i)
	{
		for (int j = i + 1; j < N; ++j)
		{
			const int sum = A[i] + A[j];
			if (sum < W)
				cache[sum] = std::make_pair(A[i], A[j]);
		}
	}
	// get result
	// exclude double used item
	// every item in the A is unique
	for (int i = 0; i < N - 1; ++i)
	{
		for (int j = i + 1; j < N; ++j)
		{
			const int rest = W - (A[i] + A[j]);
			if (rest >= 0 &&
				cache[rest].first != -1 &&
				cache[rest].first != A[i] &&
				cache[rest].first != A[j] &&
				cache[rest].second != A[i] &&
				cache[rest].second != A[j])
			{
				// found
				std::cout << "YES";
				return 0;
			}
		}
	}
	// not found
	std::cout << "NO";
	return 0;
}
