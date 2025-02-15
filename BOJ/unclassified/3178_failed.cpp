
/*
	forward trie, backward trie

	failed, MLE
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using Trie = std::vector<std::unordered_map<char, int>>;
using TrieNode = std::unordered_map<char, int>;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, K, result = 0;
	std::cin >> N >> K;
	std::vector<std::string> input(N);
	for (int i = 0; i < N; ++i)
	{
		std::cin >> input[i];
	}

	// build trie
	Trie *pforward = new Trie();
	pforward->push_back(TrieNode());
	for (const std::string& str : input)
	{
		Trie& forward = *pforward;
		int curNode = 0;
		for (int i = 0; i < K; ++i)
		{
			if (forward[curNode].find(str[i]) == forward[curNode].end())
			{
				forward[curNode].insert(
					std::make_pair(str[i], forward.size()));
				forward.push_back(TrieNode());
				result++;
			}
			curNode = forward[curNode][str[i]];
		}
	}
	delete pforward;

	Trie *pbackward = new Trie();
	pbackward->push_back(TrieNode());
	for (const std::string& str : input)
	{
		Trie& backward = *pbackward;
		int curNode = 0;
		for (int i = 2 * K - 1; i >= K; --i)
		{
			if (backward[curNode].find(str[i]) == backward[curNode].end())
			{
				backward[curNode].insert(
					std::make_pair(str[i], backward.size()));
				backward.push_back(TrieNode());
				result++;
			}
			curNode = backward[curNode][str[i]];
		}
	}
	delete pbackward;
	std::cout << result;
}