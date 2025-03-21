
#include <iostream>
#include <string>
#include <array>

int dp(const std::string &str, std::array<std::array<int, 51>, 51>& cache, int l, int r)
{
	if (cache[l][r] != 2e9)	// cache hit
	{
		return cache[l][r];
	}
	else if (l == r)	// base case
	{
		cache[l][r] = 0;
		return 0;
	}
	else if (l == r - 1)
	{
		if (str[l] == str[r])
			cache[l][r] = 0;
		else
			cache[l][r] = 1;
		return cache[l][r];
	}
	else
	{
		if (str[l] == str[r])
		{
			cache[l][r] = dp(str, cache, l + 1, r - 1);	// do not change, since it's same
		}
		cache[l][r] = std::min(cache[l][r], 1 + dp(str, cache, l + 1, r - 1));	// change left or right, + 1
		cache[l][r] = std::min(cache[l][r], 1 + dp(str, cache, l + 1, r));		// erase or add	at right, + 1
		cache[l][r] = std::min(cache[l][r], 1 + dp(str, cache, l, r - 1));		// erase or add at left, + 1
		return cache[l][r];
	}
}

int solve(const std::string &str)
{
	std::array<std::array<int, 51>, 51> cache;
	int left = 0, right = str.size() - 1;

	// cache set
	for (int i = 0; i < 51; ++i)
		std::fill(cache[i].begin(), cache[i].end(), 2e9);
	// dp
	return dp(str, cache, 0, str.size() - 1);
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::string str;
	std::cin >> str;
	// dp without swap
	int result = solve(str);
	// dp with swap
	for (int i = 0; i < str.size() - 1; ++i)
	{
		for (int j = i + 1; j < str.size(); ++j)
		{
			std::swap(str[i], str[j]);
			result = std::min(result, 1 + solve(str));	// swap, + 1
			std::swap(str[i], str[j]);
		}
	}
	std::cout << result;
}
