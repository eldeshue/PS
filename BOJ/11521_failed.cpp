
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <memory.h>

int							max_len;
int							num_strs;
char						board[8][8];
bool						visited[8][8];
bool						found[200];
std::vector<std::string>	target_strings;

bool	is_ok(std::string &str, int& str_pos, int row, int col)
{
	if (str[str_pos] == board[row][col])
	{
		if (str[str_pos] == 'q')
		{
			if (str[str_pos + 1] != 'u')
				return (false);
			str_pos += 2;
		}
		else
		{
			str_pos++;
		}
		return (true);
	}
	else
	{
		return (false);
	}
}

// handling exception, qu
bool	DFS(std::string &str, int str_pos, int r, int c)
{
	if (str.length() == str_pos)
	{
		return true;
	}
	bool result = false;
	if (0 <= r && r < max_len && 0 <= c && c <= max_len)
	{
		if (is_ok(str, str_pos, r, c))
		{
			visited[r][c] = true;
			result += DFS(str, str_pos, r - 1, c - 1);
			result += DFS(str, str_pos, r, c - 1);
			result += DFS(str, str_pos, r - 1, c);
			result += DFS(str, str_pos, r - 1, c + 1);
			result += DFS(str, str_pos, r + 1, c - 1);
			result += DFS(str, str_pos, r + 1, c);
			result += DFS(str, str_pos, r, c + 1);
			result += DFS(str, str_pos, r + 1, c + 1);
			visited[r][c] = false;
		}
	}
	return result;
}

void	found_strings()
{
	for (int i = 0; i < num_strs; ++i)
	{
		for (int r = 0; r < max_len; ++r)
		{
			for (int c = 0; c < max_len; ++c)
			{
				if (target_strings[i][0] == board[r][c])
				{
					memset(visited, 0, sizeof(visited));
					if (DFS(target_strings[i], 0, r, c))
					{
						found[i] = true;
					}
				}
			}
		}
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::string tmp;

	std::cin >> num_strs;
	target_strings.resize(num_strs);
	for (int i = 0; i < num_strs; ++i)
		std::cin >> target_strings[i];
	std::sort(target_strings.begin(), target_strings.end());
	std::cin >> max_len;
	while (max_len != 0)
	{
		memset(board, 0, sizeof(board));
		memset(found, 0, sizeof(found));
		// input
		for (int row = 0; row <  max_len; ++row)
		{
			std::cin >> tmp;
			for (int col = 0; col <  max_len; ++col)
			{
				board[row][col] = tmp[col];
			}
		}
		// solve, DFS, Backtracking.
		found_strings();
		// print result
		for (int i = 0; i < num_strs; ++i)
		{
			if (found[i] == true)
			{
				std::cout << target_strings[i] << "\n";
			}
		}
		std::cout << "-\n";
		std::cin >> max_len;
	}
}