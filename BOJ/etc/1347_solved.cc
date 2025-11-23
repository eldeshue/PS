/*
	BOJ
*/
#include <iostream>
#include <vector>
#include <string>

using P = std::pair<int, int>;
P constexpr dir[4] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
// L -> +, R -> -

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	std::string command;
	std::cin >> N >> command;

	// count map size
	P row_range = { 0, 0 }, col_range = { 0, 0 };
	P cur_pos = { 0, 0 };
	int cur_dir = 0;
	for (char const c : command)
	{
		if (c == 'L')
		{
			cur_dir = (cur_dir + 1) % 4;
		}
		else if (c == 'R')
		{
			cur_dir = (cur_dir + 3) % 4;
		}
		else
		{
			// move
			cur_pos.first += dir[cur_dir].first;
			cur_pos.second += dir[cur_dir].second;
			// update range
			row_range.first = std::min(row_range.first, cur_pos.first);
			row_range.second = std::max(row_range.second, cur_pos.first);
			col_range.first = std::min(col_range.first, cur_pos.second);
			col_range.second = std::max(col_range.second, cur_pos.second);
		}
	}

	// paint map
	int col_size = col_range.second - col_range.first + 1;
	int row_size = row_range.second - row_range.first + 1;
	std::vector<std::string> map(row_size, std::string(col_size, '#'));
	cur_pos = { -row_range.first, -col_range.first };
	cur_dir = 0;
	map[cur_pos.first][cur_pos.second] = '.';
	for (char const c : command)
	{
		if (c == 'L')
		{
			cur_dir = (cur_dir + 1) % 4;
		}
		else if (c == 'R')
		{
			cur_dir = (cur_dir + 3) % 4;
		}
		else // 'F'
		{
			// move
			cur_pos.first += dir[cur_dir].first;
			cur_pos.second += dir[cur_dir].second;
		}
		map[cur_pos.first][cur_pos.second] = '.';
	}

	// print map
	for (auto const& row : map)
		std::cout << row << '\n';
}
