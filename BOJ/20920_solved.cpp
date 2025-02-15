
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::unordered_map<std::string, int> freq;
	std::string input;
	int N, M;
	std::cin >> N >> M;
	std::vector<std::string> words;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> input;
		if (input.size() >= M)
		{
			if (++freq[input] == 1)
				words.push_back(input);
		}
	}
	std::sort(words.begin(), words.end(), [&](std::string const& str1, std::string const& str2) {
		if (freq[str1] == freq[str2])
		{
			if (str1.size() == str2.size())
			{
				return str1 < str2;
			}
			return str1.size() > str2.size();
		}
		return freq[str1] > freq[str2];
		});
	// result
	for (const auto& w : words)
	{
		std::cout << w << '\n';
	}
}