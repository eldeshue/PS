
/*

	boj 1039, 교환.

	상태공간의 완전탐색, 어떻게 중복을 처리할 것인가?

	홀수번째에 도달한 상태는 마찬가지로 홀수번째에 도달가능함.
	마찬가지로 짝수번째에 도달한 상태는 짝수번째에 도달가능함.
	이는 동일한 행동을 반복하는 것으로 얻을 수 있는 상태이기 때문임.

	예외적으로 짝수 홀수 모두 도달 가능한 상태라면 별도로 처리해줌.
	따라서 상태 별로 가능한 부류가 3종 존재함.
	0 : 짝수
	1 : 홀수
	2 : 둘 다
	-> 해시맵에 기록함.

	큐에 집어넣는 상태는 string, depth가 됨.

*/
#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>

using stat = std::pair<std::string, int>;

std::string swap_num(std::string origin, int idx1, int idx2)
{
	std::string result = origin;
	std::swap(result[idx1], result[idx2]);
	return result;
}

void bfs(std::string& sstart, int max_depth)
{
	std::unordered_map<std::string, int> visited_table;
	std::queue<stat> nextQ;
	nextQ.push(std::make_pair(sstart, 0));

	// search
	int next_depth;
	std::string cur_num, next_num;
	while (!nextQ.empty())
	{
		cur_num = nextQ.front().first;
		next_depth = nextQ.front().second + 1;
		nextQ.pop();
		if (next_depth > max_depth)
		{
			break ;
		}
		// swap
		for (int i = 0; i < cur_num.size() - 1; ++i)
		{
			for (int j = i + 1; j < cur_num.size(); ++j)
			{
				next_num = swap_num(cur_num, i, j);
				// new
				if (next_num[0] == '0')
				{
					continue ;
				}
				else if (visited_table.find(next_num) == visited_table.end())
				{
					visited_table.insert(std::make_pair(next_num, 1 & next_depth));
					nextQ.push(std::make_pair(next_num, next_depth));
				}
				else if (visited_table[next_num] != 2 && visited_table[next_num] != (1 & next_depth))
				{
					visited_table[next_num] = 2;
				}
			}
		}
	}
	// find max value of the string
	int result = -1;
	for (auto itr = visited_table.begin(); itr != visited_table.end(); ++itr)
	{
		int num = std::stoi(itr->first);
		if ((itr->second == (1 & max_depth) || itr->second == 2) && result < num)
		{
			result = num;
		}
	}
	// print result
	std::cout << result;
	return ;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::string N; int K;
	std::cin >> N >> K;
	if (N.size() < 2)
	{
		std::cout << -1;
		return 0;
	}
	bfs(N, K);
}
