
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	std::unordered_map<std::string, int> pattern;

	int R, C, k;
	std::cin >> R >> C;
	std::vector<std::string> inputVec(R);
	for (int i = 0; i < R; ++i)
	{
		std::cin >> inputVec[i];
	}
	std::cin >> k;

	// count pattern
	for (const std::string& str : inputVec)
	{
		if (pattern.find(str) == pattern.end())
		{
			int zeroCnt = 0;
			for (const char& c : str)
			{
				if (c == '0')
					zeroCnt++;
			}
			if ((zeroCnt <= k) && ((zeroCnt & 1) == (k & 1)))
			{
				pattern.insert(std::make_pair(str, 1));
			}
		}
		else
		{
			pattern[str]++;
		}

	}

	// get max value
	int maxCnt = 0;
	for (const auto& entry : pattern)
	{
		maxCnt = std::max(maxCnt, entry.second);
	}
	std::cout << maxCnt;
}