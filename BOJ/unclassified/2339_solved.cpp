
#include <iostream>
#include <vector>
#include <memory.h>

char board[9][9];
std::vector<std::pair<int, int>> empty_points;

void check_point(std::vector<int>& values, int row, int col)
{
	int row_offset = (row / 3) * 3;
	int col_offset = (col / 3) * 3;
	bool is_ok[10];

	memset(is_ok, -1, sizeof(is_ok));
	// row
	for (int i = 0; i < 9; ++i)
		is_ok[board[row][i]] = false;
	// col
	for (int i = 0; i < 9; ++i)
		is_ok[board[i][col]] = false;
	// block
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			is_ok[board[row_offset + i][col_offset + j]] = false;
		}
	}
	// push
	for (int i = 1; i <= 9; ++i)
		if (is_ok[i])
			values.push_back(i);
}

void DFS(bool& is_found, int cur_empty_index)
{
	if (is_found)
	{
		return;
	}
	/*
	if (cur_empty_index == 23)
	{
		for (int i = 0; i < 9; ++i)
		{
			for (int j = 0; j < 9; ++j)
			{
				std::cout << static_cast<int>(board[i][j]);
			}
			std::cout << '\n';
		}
	}
	*/
	if (cur_empty_index == empty_points.size())
	{
		for (int i = 0; i < 9; ++i)
		{
			for (int j = 0; j < 9; ++j)
			{
				std::cout << static_cast<int>(board[i][j]);
			}
			std::cout << '\n';
		}
		is_found = true;
		return;
	}
	std::vector<int> potential_values;
	int cur_row = empty_points[cur_empty_index].first;
	int cur_col = empty_points[cur_empty_index].second;
	check_point(potential_values, cur_row, cur_col);
	for (const auto cur_val : potential_values)
	{
		board[cur_row][cur_col] = cur_val;
		DFS(is_found, cur_empty_index + 1);
		board[cur_row][cur_col] = 0;
		if (is_found)
		{
			return;
		}
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			std::cin >> board[i][j];
			board[i][j] -= '0';
			if (board[i][j] == 0)
				empty_points.push_back(std::make_pair(i, j));
		}
	}
	bool is_solution_found = false;
	DFS(is_solution_found, 0);
}