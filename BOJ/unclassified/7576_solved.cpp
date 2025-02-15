
#include <iostream>
#include <queue>
#include <tuple>
#include <memory.h>

int M, N;
int visited[1000][1000];

bool is_ok_to_push(int row, int col)
{
	if (0 <= row && row < M && 0 <= col && col < N)
	{
		if (visited[row][col] == 0)
		{
			return true;
		}
	}
	return false;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(visited, 0, sizeof(visited));
	
	std::queue<std::tuple<int, int, int>> Q;
	// input
	std::cin >> N >> M;
	for (int r = 0; r < M; ++r)
	{
		for (int c = 0; c < N; ++c)
		{
			std::cin >> visited[r][c];
			if (visited[r][c] == 1)
			{
				Q.push(std::make_tuple(r, c, 1));
			}
		}
	}
	// BFS
	while (!Q.empty())
	{
		int cur_row = std::get<0>(Q.front());
		int cur_col = std::get<1>(Q.front());
		int cur_val = std::get<2>(Q.front());
		Q.pop();
		if (is_ok_to_push(cur_row - 1, cur_col)) // up
		{
			visited[cur_row - 1][cur_col] = cur_val + 1;
			Q.push(std::make_tuple(cur_row - 1, cur_col, cur_val + 1));
		}
		if (is_ok_to_push(cur_row + 1, cur_col)) // down
		{
			visited[cur_row + 1][cur_col] = cur_val + 1;
			Q.push(std::make_tuple(cur_row + 1, cur_col, cur_val + 1));
		}
		if (is_ok_to_push(cur_row, cur_col - 1)) // left
		{
			visited[cur_row][cur_col - 1] = cur_val + 1;
			Q.push(std::make_tuple(cur_row, cur_col - 1, cur_val + 1));
		}
		if (is_ok_to_push(cur_row, cur_col + 1)) // right
		{
			visited[cur_row][cur_col + 1] = cur_val + 1;
			Q.push(std::make_tuple(cur_row, cur_col + 1, cur_val + 1));
		}
	}
	// find max: if 0 remain, return -1.
	int result = 1;
	bool empty_flag = 0;
	for (int r = 0; r < M; ++r)
	{
		for (int c = 0; c < N; ++c)
		{
			result = std::max(result, visited[r][c]);
			if (visited[r][c] == 0)
			{
				result = 0;
				empty_flag = 1;
				break;
			}
		}
		if (empty_flag)
		{
			break;
		}
	}
	std::cout << result - 1 << "\n";
}