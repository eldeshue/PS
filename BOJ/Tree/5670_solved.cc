
/*
	Trie, very slow.

	quick implementation, slow run.
	need to optimize trie using array.
*/
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>
#include <unordered_map>

using TrieNode = std::unordered_map<char, int>;
using Trie = std::vector<TrieNode>;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	while (std::cin >> N)
	{
		std::vector<std::string> strs(N);
		for (auto &str : strs)
			std::cin >> str;
		// build trie
		Trie trie(1);
		trie[0].insert(std::make_pair(-1, -1)); // add ghost node to identify end
		for (const std::string &str : strs)
		{
			int curPos = 0;
			for (int i = 0; i <= str.size(); ++i)
			{
				if (i == str.size())
				{
					// add ghost node to identify end
					trie[curPos].insert(std::make_pair(-1, -1));
					break;
				}
				const char c = str[i];
				if (trie[curPos].find(c) == trie[curPos].end()) // add new node
				{
					trie[curPos].insert(std::make_pair(c, trie.size()));
					trie.push_back(TrieNode());
				}
				curPos = trie[curPos][c];
			}
		}
		// count result, traverse trie
		int pressCount = 0;
		for (const std::string &str : strs)
		{
			int curPos = 0;
			for (const char c : str)
			{
				if (trie[curPos].size() > 1)
				{
					++pressCount;
				}
				curPos = trie[curPos][c];
			}
		}
		// print result
		//		std::cout << pressCount << '\n';
		std::cout << std::fixed << std::setprecision(2) << std::roundf((static_cast<float>(pressCount) / N) * 100.0f) / 100.0f << '\n';
	}
}
