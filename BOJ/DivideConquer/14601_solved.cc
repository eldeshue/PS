
#include <iostream>
#include <vector>
#include <tuple>

using Board = std::vector<std::vector<int>>;
using Crd = std::pair<int, int>;
using Range = std::tuple<int, int, int, int>;

bool is_target_in_range(Range const& rng, Crd const& target)
{
	auto const& [sx, ex, sy, ey] = rng;
	auto const& [tx, ty] = target;
	return
		(sx <= tx) &&
		(tx < ex) &&
		(sy <= ty) &&
		(ty < ey);
}

// paint quadrant except a quadrant with the target
void paint_quadrant_recursively(Board& b, int& color, Range const rng, Crd const target)
{
	auto const [sx, ex, sy, ey] = rng;
	auto const [tx, ty] = target;
	int const len = ex - sx;

	if (len == 2)	// base case, paint
	{
		for (int y = sy; y < ey; ++y)
		{
			for (int x = sx; x < ex; ++x)
			{
				if (!(y == ty && x == tx))
				{
					b[y][x] = color;
				}
			}
		}
		color++;
		return;
	}

	int c = 0;
	int const new_len = len >> 1;
	const Crd corner_center[4] = {	// 각 사분면의 중앙 4개의 칸의 좌표
		{sx + new_len - 1, sy + new_len - 1},
		{sx + new_len, sy + new_len - 1},
		{sx + new_len - 1, sy + new_len},
		{sx + new_len, sy + new_len},
	};

	// for each quadrant
	for (int nsy = sy; nsy < ey; nsy += new_len)
	{
		for (int nsx = sx; nsx < ex; nsx += new_len)
		{
			// get new range
			auto new_rng = std::make_tuple(nsx, nsx + new_len, nsy, nsy + new_len);

			// recurse
			if (is_target_in_range(new_rng, target))
			{
				// target in this quadrant
				// paint center
				paint_quadrant_recursively(b, color, { sx + new_len - 1, sx + new_len + 1, sy + new_len - 1, sy + new_len + 1 }, corner_center[c]);

				// go in to the deep, search target
				paint_quadrant_recursively(b, color, new_rng, target);
			}
			else
			{
				// paint other quadrant
				paint_quadrant_recursively(b, color, new_rng, corner_center[c]);
			}

			// for center pos
			c++;
		}
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	int k, tx, ty;
	std::cin >> k >> tx >> ty;
	tx--; ty--;

	// solve
	int const len = 1 << k;
	Board board(len, std::vector<int>(len, -1));
	int color = 1;
	paint_quadrant_recursively(board, color, std::make_tuple(0, len, 0, len), Crd(tx, ty));

	// print row reverse
	for (int r = len - 1; r >= 0; --r)
	{
		for (int c = 0; c < len; ++c)
		{
			std::cout << board[r][c] << ' ';
		}
		std::cout << '\n';
	}
}

