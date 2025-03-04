

#include <iostream>
#include <functional>
#include <vector>

int main()
{
				std::ios_base::sync_with_stdio(false);
				std::cin.tie(nullptr);
				std::cout.tie(nullptr);
				
				// using pascal's identity, dp
				std::vector<std::vector<int>> cache(1001, std::vector<int>(1001, -1));
				std::function<int(int const, int const)> memoize = [&](int const n, int const k) {
								if (k == 0 || n == k)
								{
												return 1;
								}
								else if (k == 1)
								{
												return n;
								}
								else if (cache[n][k] != -1)
								{
												return cache[n][k];
								}
								else
								{
												return cache[n][k] = (memoize(n - 1, k) + memoize(n - 1, k - 1)) % 10007;
								}
				};
				int N, K;
				std::cin >> N >> K;
				std::cout << memoize(N, K);
}
