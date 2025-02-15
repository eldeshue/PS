
#include <iostream>
#include <memory.h>
#include <cmath>

int board[14];
bool visited_row[14];
bool visited_diag1[28];
bool visited_diag2[28];
int result, N;

void dfs(int cur_col)
{
	if (cur_col == N)
	{
		result++;
		return ;
	}

	for (int i = 0; i < N; ++i)
	{
		if (!visited_row[i] 
			&& !visited_diag1[cur_col + i] 
			&& !visited_diag2[N + cur_col - i])
		{
			board[cur_col] = i;
			visited_row[i] = true;
			visited_diag1[cur_col + i] = true;
			visited_diag2[N + cur_col - i] = true;
			dfs(cur_col + 1);
			visited_row[i] = false;
			visited_diag1[cur_col + i] = false;
			visited_diag2[N + cur_col - i] = false;
		}
	}
	return ;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(board, 0, sizeof(board));
	memset(visited_row, 0, sizeof(visited_row));
	memset(visited_diag1, 0, sizeof(visited_diag1));
	memset(visited_diag2, 0, sizeof(visited_diag2));

	result = 0;
	std::cin >> N;
	dfs(0);
	std::cout << result;
}
