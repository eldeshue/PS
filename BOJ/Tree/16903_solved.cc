
/*
	BOJ 16903

	trie를 이용하여 쿼리를 처리하는 문제

	node에 counter를 두어 해당 경로의 존재성을 표현한다.
*/
#include <iostream>
#include <deque>
#include <array>

using Node = std::array<int, 2>;	// binary trie

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// binary trie
	std::deque<Node> trie;
	trie.push_back({ -1, -1 });
	std::deque<int> freq;
	freq.push_back(1e9);
	auto add_query = [&](int x) {
		int cur_node = 0;
		for (int i = 31; i >= 0; --i)
		{
			int cur_char = !!(x & (1 << i));
			int& next_node = trie[cur_node][cur_char];
			if (next_node == -1)	// insert node
			{
				next_node = trie.size();
				trie.push_back({ -1, -1 });
				freq.push_back(0);
			}
			freq[next_node]++;
			cur_node = next_node;
		}
		};
	auto sub_query = [&](int x) {
		int cur_node = 0;
		for (int i = 31; i >= 0; --i)
		{
			int cur_char = !!(x & (1 << i));
			int next_node = trie[cur_node][cur_char];
			freq[next_node]--;
			cur_node = next_node;
		}
		};
	auto get_opposite_query = [&](int x) -> int {
		int result = 0;
		int cur_node = 0;
		for (int i = 31; i >= 0; --i)
		{
			// find opposite
			int cur_char = !(x & (1 << i));
			int next_node = trie[cur_node][cur_char];
			if (next_node == -1 || freq[next_node] == 0)
			{
				// no opposite, follow same
				// reverse again
				cur_char = !cur_char;
				next_node = trie[cur_node][cur_char];
			}
			result |= (cur_char << i);	// mark result
			cur_node = next_node;
		}
		return result;
		};
	add_query(0);

	int M;
	std::cin >> M;
	while (M--)
	{
		int t, x;
		std::cin >> t >> x;
		if (t == 1)
		{
			add_query(x);
		}
		else if (t == 2)
		{
			sub_query(x);
		}
		else // t == 3
		{
			std::cout << static_cast<int>(x ^ get_opposite_query(x)) << '\n';
		}
	}
}
