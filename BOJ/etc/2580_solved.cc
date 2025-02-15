
#include <iostream>
#include <functional>
#include <vector>

using Board = std::array<std::array<int, 9>, 9>;
using Segment = std::vector<bool>;
using DB = std::vector<Segment>;
using pii = std::pair<int, int>;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	Board b;
	DB rowDB(9, Segment(10, false));
	DB colDB(9, Segment(10, false));
	DB blockSeg(9, Segment(10, false));
	std::vector<pii> emptyPos;
	auto getBlockNum = [](int row, int col)
	{
		return (row / 3) * 3 + col / 3;
	};
	auto isValOkAtPos = [&](const int row, const int col, const int val)
	{
		return !(rowDB[row][val]) && !(colDB[col][val]) && !(blockSeg[getBlockNum(row, col)][val]);
	};
	auto setValAtPos = [&](const int row, const int col, const int val)
	{
		rowDB[row][val] = true;
		colDB[col][val] = true;
		blockSeg[getBlockNum(row, col)][val] = true;
		b[row][col] = val;
	};
	auto unsetValAtPos = [&](const int row, const int col, const int val)
	{
		rowDB[row][val] = false;
		colDB[col][val] = false;
		blockSeg[getBlockNum(row, col)][val] = false;
		b[row][col] = 0;
	};
	auto printBoard = [&b]()
	{
		for (int r = 0; r < 9; ++r)
		{
			for (int c = 0; c < 9; ++c)
				std::cout << b[r][c] << ' ';
			std::cout << '\n';
		}
	};
	std::function<bool(int)> backTrack = [&](const int curIdx)
	{
		if (curIdx == emptyPos.size())
		{
			printBoard(); // printing results
			return true;
		}
		else
		{
			const auto [curRow, curCol] = emptyPos[curIdx];
			bool result = false;
			for (int v = 1; v <= 9; ++v) // back tracking
			{
				if (isValOkAtPos(curRow, curCol, v))
				{
					setValAtPos(curRow, curCol, v);
					result |= backTrack(curIdx + 1);
					unsetValAtPos(curRow, curCol, v);
					if (result)
						break;
				}
			}
			return result;
		}
	};

	for (int r = 0; r < 9; ++r)
	{
		for (int c = 0; c < 9; ++c)
		{
			std::cin >> b[r][c];
			if (b[r][c])
			{
				setValAtPos(r, c, b[r][c]);
			}
			else
			{
				emptyPos.push_back({r, c});
			}
		}
	}

	// back track
	backTrack(0);
}
