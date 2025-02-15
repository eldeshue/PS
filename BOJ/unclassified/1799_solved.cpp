
#include <iostream>
#include <memory.h>

int size;
bool board[10][10];	// ÁÂÇ¥ÀÇ ÇÕÀÌ Â¦¼ö
bool diag[2][19];	// visited

int DFS_half(bool is_white, int cnt, int pos)
{
	int result = 0;
	bool flag = true;
	for (int x = pos; x < size * size; ++x)
	{
		int i = x / size;
		int j = x % size;
		if (is_white != ((i + j) & 1)) // black or white
		{
			continue;
		}
		if (board[i][j] && !diag[0][i + j] && !diag[1][size - 1 - i + j])
		{
			flag = false;
			diag[0][i + j] = true;
			diag[1][size - 1 - i + j] = true;
			result = std::max(result, DFS_half(is_white, cnt + 1, x + 1));
			diag[0][i + j] = false;
			diag[1][size - 1 - i + j] = false;
		}
	}
	if (flag)
		result = cnt;
	return result;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(board, 0, sizeof(board));
	memset(diag, 0, sizeof(diag));

	std::cin >> size;
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			std::cin >> board[i][j];
		}
	}
	std::cout << DFS_half(true, 0, 0) + DFS_half(false, 0, 0) << '\n';
}
