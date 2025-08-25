/*
	BOJ 13505

	binary trie, find as oposite as possible
*/
#include <array>
#include <deque>
#include <iostream>
#include <vector>

using uint = unsigned int;
using Node = std::array<int, 2>;
using BinaryTrie = std::deque<Node>;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	int N;
	std::cin >> N;
	std::vector<uint> nums(N);
	for (auto& n : nums)
		std::cin >> n;

	// build trie
	BinaryTrie trie;
	trie.push_back({ -1, -1 });
	for (auto A : nums)
	{
		int cur_node = 0;
		for (int i = 31; i >= 0; --i)
		{
			bool next_idx = (A >> i) & 1;
			if (trie[cur_node][next_idx] == -1)
			{
				trie[cur_node][next_idx] = trie.size();
				trie.push_back({ -1, -1 });
			}

			cur_node = trie[cur_node][next_idx];
		}
	}

	// find max XOR result
	uint result = 0;
	for (auto A : nums)
	{
		uint invA = 0;
		int cur_node = 0;
		// find opposite
		for (int i = 31; i >= 0; --i)
		{
			bool next_idx = !((A >> i) & 1);
			if (trie[cur_node][next_idx] == -1)
				next_idx = !next_idx;	// 없으면 같은 방향으로...

			invA |= (next_idx << i);

			cur_node = trie[cur_node][next_idx];
		}

		result = std::max(result, A ^ invA);
	}

	std::cout << result;
}