
#include <iostream>
#include <string>
#include <array>

std::array<std::pair<int, int>, 8> dir;

bool is_in_range(int x, int y)
{
	return (0 <= x) && (x < 8) && (0 <= y) && (y < 8);
}

void set_dir()
{
	dir[0] = std::make_pair(1, 0);
	dir[1] = std::make_pair(-1, 0);
	dir[2] = std::make_pair(0, -1);
	dir[3] = std::make_pair(0, 1);
	dir[4] = std::make_pair(1, 1);
	dir[5] = std::make_pair(-1, 1);
	dir[6] = std::make_pair(1, -1);
	dir[7] = std::make_pair(-1, -1);
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	set_dir();

	int num_query;
	std::pair<int, int> king, ball;
	std::string input;
	std::cin >> input;
	king = std::make_pair(input[0] - 'A', input[1] - '1');
	std::cin >> input;
	ball = std::make_pair(input[0] - 'A', input[1] - '1');
	std::cin >> num_query;
	while (num_query--)
	{
		std::cin >> input;
		int dir_idx;
		if (input == "R")
			dir_idx = 0;
		else if (input == "L")
			dir_idx = 1;
		else if (input == "B")
			dir_idx = 2;
		else if (input == "T")
			dir_idx = 3;
		else if (input == "RT")
			dir_idx = 4;
		else if (input == "LT")
			dir_idx = 5;
		else if (input == "RB")
			dir_idx = 6;
		else if (input == "LB")
			dir_idx = 7;
		int next_x = king.first + dir[dir_idx].first;
		int next_y = king.second + dir[dir_idx].second;
		if (is_in_range(next_x, next_y))	// is king in range?
		{
			if ((next_x == ball.first)
				&& (next_y == ball.second))	// collide 
			{
				if (!is_in_range(next_x + dir[dir_idx].first,
					next_y + dir[dir_idx].second))	// is ball in range?
					continue;
				ball.first = next_x + dir[dir_idx].first;
				ball.second = next_y + dir[dir_idx].second;
			}
			king.first = next_x;
			king.second = next_y;
		}
	}
	std::cout << static_cast<char>(king.first + 'A') << king.second + 1 << '\n'
		<< static_cast<char>(ball.first + 'A') << ball.second + 1 << '\n';
}
