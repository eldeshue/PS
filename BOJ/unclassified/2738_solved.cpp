
#include <iostream>
#include <memory.h>

int matrix[100][100];

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(matrix, 0, sizeof(matrix));

	int max_row, max_col, temp;
	std::cin >> max_row >> max_col;
	for (int y = 0; y < max_row; ++y)
	{
		for (int x = 0; x < max_col; ++x)
		{
			std::cin >> matrix[y][x];
		}
	}
	for (int y = 0; y < max_row; ++y)
	{
		for (int x = 0; x < max_col; ++x)
		{
			std::cin >> temp;
			matrix[y][x] += temp;
		}
	}
	for (int y = 0; y < max_row; ++y)
	{
		for (int x = 0; x < max_col; ++x)
		{
			std::cout << matrix[y][x] << " ";
		}
		std::cout << "\n";
	}
}