
#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
#include <unordered_set>

using psi = std::pair<std::string, int>;

int N, K;
std::string sorted_str;

std::string rev_r_k(std::string str, int pos)
{
	for (int i = 0; i < K / 2; ++i)
	{
		std::swap(str[pos + i], str[pos + K - 1 - i]);
	}
	return str;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int n;
	std::string input;
	std::cin >> N >> K;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> n;
		input.push_back(static_cast<char>('0' + n));
	}
	// BFS
	std::unordered_set<std::string> visited_state;
	std::queue<psi> Q;
	Q.push(std::make_pair(input, 0));
	visited_state.insert(input);
	std::sort(input.begin(), input.end());
	sorted_str = input;
	if (sorted_str == Q.front().first)
	{
		std::cout << 0;
		return 0;
	}
	while (!Q.empty())
	{
		std::string cur_state = Q.front().first;
		int next_step = Q.front().second + 1;
		Q.pop();
		for (int i = 0; i < N - K + 1; ++i)
		{
			std::string next = rev_r_k(cur_state, i);
			if (next == sorted_str)
			{
				std::cout << next_step;
				return 0;
			}
			else if (visited_state.find(next) == visited_state.end())
			{
				visited_state.insert(next);
				Q.push(std::make_pair(next, next_step));
			}
		}
	}
	std::cout << -1;
	return 0;
}