// using DP
#include <iostream>

int memo[41][2];

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	memo[0][0] = 1;
	memo[0][1] = 0;
	memo[1][0] = 0;
	memo[1][1] = 1;
	for (int i = 2; i <= 40; ++i)
	{
		memo[i][0] = memo[i - 1][0] + memo[i - 2][0];
		memo[i][1] = memo[i - 1][1] + memo[i - 2][1];
	}

	int numTest, test;
	std::cin >> numTest;
	for (int i = 0; i < numTest; ++i)
	{
		std::cin >> test;
		std::cout << memo[test][0] << " " << memo[test][1] << "\n";
	}

}