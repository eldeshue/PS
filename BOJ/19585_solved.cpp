
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string>
#include <string_view>

static bool isLegendary(
	const std::vector<std::unordered_map<char, int>> &pTrie,
	const std::unordered_set<std::string_view> &sSet,
	const std::string &target
	)
{
	int curPos = 0;
	for (int idx = 0; idx < target.size(); ++idx)
	{
		if ((pTrie[curPos].find('E') != pTrie[curPos].end())
			&& (sSet.find(std::string_view(target.begin() + idx,
				target.end())) != sSet.end()))
		{
			return true;
		}
		else if (pTrie[curPos].find(target[idx]) != pTrie[curPos].end())
		{
			curPos = pTrie[curPos].at(target[idx]);
		}
		else
		{
			break;
		}
	}
	return false;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::string input;
	std::vector<std::unordered_map<char, int>> prefixTrie;
	prefixTrie.push_back(std::unordered_map<char, int>());
	std::unordered_set<std::string_view> suffixSet;
	int C, N, Q;
	std::cin >> C >> N;
	std::vector<std::string> suffix(N);
	for (int i = 0; i < C; ++i)
	{
		// build trie
		std::cin >> input;
		int curPos = 0;
		for (int i = 0; i < input.size(); ++i)
		{
			if (prefixTrie[curPos].find(input[i])
				== prefixTrie[curPos].end())
			{
				prefixTrie[curPos].insert(
					std::make_pair(input[i], prefixTrie.size()));
				prefixTrie.push_back(std::unordered_map<char, int>());
			}
			curPos = prefixTrie[curPos][input[i]];
		}
		// mark end
		prefixTrie[curPos].insert(std::make_pair('E', -1));
	}
	for (int i = 0; i < N; ++i)
	{
		std::cin >> suffix[i];
		suffixSet.insert(std::string_view(suffix[i].begin(), suffix[i].end()));
	}
	std::cin >> Q;
	for (int i = 0; i < Q; ++i)
	{
		std::cin >> input;
		if (isLegendary(prefixTrie, suffixSet, input))
		{
			std::cout << "Yes\n";
		}
		else
		{
			std::cout << "No\n";
		}
	}
}