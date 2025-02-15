
/*
	BOJ 7682. Tic Tac Toe

	틱택토를 함수형으로 구현하자.

	틱택토의 입력은 3X3의 보드, 출력은 게임의 상태값.

	함수형 프로그래밍으로 입력 데이터를 프로세싱하여 출력데이터로 변환한다.
	즉 함수형 프로그래밍이란, 여러 함수를 결합하여 하나의 커다란 함수를 만드는 과정이다.

	=======================================

	보드의 입력에서 validity를 체크하는 문제.

	validity는 보드의 상태가 게임 과정에서 최종적으로 있을 수 있는 상태인지 여부.

	1. sanity check.
		board를 구성하는 X의 수가 O의 수와 같거나 1 더 많아야 함. X부터 번갈아 한 번씩 플레이 함.
	2. 게임의 승패 여부
		둘 중 한 쪽의 승리, 또는 board가 full인데 둘 다 승리에 실패하는 경우(무승부).
*/
#include <iostream>
#include <functional>
#include <numeric>
#include <algorithm>
#include <string>
#include <vector>

using Line = std::vector<char>;
using Lines = std::vector<Line>;
using Board = std::vector<Line>;
using Coordinate = std::pair<int, int>;

/*
	basic high degree functions

	building blocks for functional programming.
*/
// return logicla AND for all item in the collection after applying lambda
auto allOfCollection = [](const auto &collection, auto lambda)
{
	return std::all_of(collection.begin(), collection.end(), lambda);
};

auto anyOfCollection = [](const auto &collection, auto lambda)
{
	return std::any_of(collection.begin(), collection.end(), lambda);
};

auto noneOfCollections = [](const auto &collection, auto lambda)
{
	return std::none_of(collection.begin(), collection.end(), lambda);
};

// map
// return a new collection after applying lambda to the source collection
template <typename Destination>
auto transformAll = [](const auto &source, auto lambda)
{
	Destination result;
	result.reserve(source.size());
	std::transform(source.begin(), source.end(), std::back_inserter(result), lambda);
	return result;
};

// reduce
auto accumulateAll = [](auto source, auto lambda)
{
	return std::accumulate(source.begin(), source.end(), decltype(source)::value_type(), lambda);
};

// concatenate collections
// make copy of first + second
// result is not const, so first must not be a const
auto concatenate = [](auto first, const auto second)
{
	auto result(first);
	result.insert(result.end(), std::make_move_iterator(second.begin()), std::make_move_iterator(second.end()));
	return result;
};

// -------------------------------------------------------------- //

auto lineFilledWith = [](const auto &line, const auto tokenToCheck)
{ return allOfCollection(line, [tokenToCheck](const auto &token)
						 { return token == tokenToCheck; }); };
auto lineFilledWithX = std::bind(lineFilledWith, std::placeholders::_1, 'X');
auto lineFilledWithO = std::bind(lineFilledWith, std::placeholders::_1, 'O');

auto linehasEmpty = [](const auto &line)
{
	return anyOfCollection(line, [](const auto c)
						   { return c == '.'; });
};

// get data from board, at certain coordinate
auto accessAtCoordinate = [](const auto &board, const Coordinate &coordinate)
{
	return board[coordinate.first][coordinate.second];
};

// transform coordinates to it's data
auto projectCoordinates = [](const auto &board, const auto &coordinates)
{
	auto boardElementFromCoordinates = std::bind(accessAtCoordinate, board, std::placeholders::_1);
	return transformAll<Line>(coordinates, boardElementFromCoordinates);
};

// make range for the process, not lazy, cause some overhead
auto toRange = [](auto const collection)
{
	std::vector<int> range(collection.size());
	//	std::iota(std::begin(range), std::end(range), 0);
	std::iota(range.begin(), range.end(), 0);
	return range;
};

// get coordinates of rows
auto lineCoordinates = [](const auto board, auto lineIndex)
{
	auto range = toRange(board);
	return transformAll<std::vector<Coordinate>>(range, [lineIndex](auto index)
												 { return std::make_pair(lineIndex, index); });
};

// get data of rows
auto line = [](auto board, int lineIndex)
{
	return projectCoordinates(board, lineCoordinates(board, lineIndex));
};

// get coordinates of columns
auto columnCoordinates = [](const auto board, auto columnIndex)
{
	auto range = toRange(board);
	return transformAll<std::vector<Coordinate>>(range, [columnIndex](const auto index)
												 { return std::make_pair(index, columnIndex); });
};

// get data of columns
auto column = [](auto board, auto columnIndex)
{
	return projectCoordinates(board, columnCoordinates(board, columnIndex));
};

// get coordinates of main diagonal
auto mainDiagonalCoordinates = [](const auto board)
{
	auto range = toRange(board);
	return transformAll<std::vector<Coordinate>>(range, [](auto index)
												 { return std::make_pair(index, index); });
};

auto mainDiagonal = [](const auto board)
{
	return projectCoordinates(board, mainDiagonalCoordinates(board));
};

auto secondaryDiagonalCoordinates = [](const auto board)
{
	auto range = toRange(board);
	return transformAll<std::vector<Coordinate>>(range, [&board](auto index)
												 { return std::make_pair(index, board.size() - 1 - index); });
};

auto secondaryDiagonal = [](const auto board)
{
	return projectCoordinates(board, secondaryDiagonalCoordinates(board));
};

// get all lines from the board
// from range of index, get it's corresponding line
auto allLines = [](auto board)
{
	auto range = toRange(board);
	return transformAll<Lines>(range, [&board](auto index)
							   { return line(board, index); });
};

auto allColumns = [](auto board)
{
	auto range = toRange(board);
	return transformAll<Lines>(range, [&board](auto index)
							   { return column(board, index); });
};

auto allDiagonals = [](auto board) -> Lines
{
	return {mainDiagonal(board), secondaryDiagonal(board)}; // initialize list
};

auto allLinesColumnsDiagonals = [](const auto board)
{
	return concatenate(concatenate(allLines(board), allColumns(board)), allDiagonals(board));
};

// count board status
auto countIf = [](const auto &collection, auto lambda)
{
	int cnt = 0;
	for (const auto &row : collection)
	{
		for (const auto &item : row)
		{
			if (lambda(item))
				cnt++;
		}
	}
	return cnt;
};

// get results
auto xWins = [](const auto &board)
{
	return anyOfCollection(allLinesColumnsDiagonals(board), lineFilledWithX);
};

auto oWins = [](const auto &board)
{
	return anyOfCollection(allLinesColumnsDiagonals(board), lineFilledWithO);
};

auto isFull = [](const auto &board)
{
	return !anyOfCollection(allLinesColumnsDiagonals(board), linehasEmpty);
};

// -------------------------------------------- //
auto solve = [](const auto &board)
{
	auto xCnt = countIf(board, [](const char c)
						{ return c == 'X'; });
	auto oCnt = countIf(board, [](const char c)
						{ return c == 'O'; });
	bool xWin = xWins(board);
	bool oWin = oWins(board);
	bool full = isFull(board);
	return ((xCnt - oCnt == 1) && xWin && !oWin) || ((xCnt == oCnt) && oWin && !xWin) || (full && (xCnt - oCnt == 1) && (!xWin && !oWin));
};

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	std::string input;
	std::vector<std::vector<char>> board(3, std::vector<char>(3));

	while (true)
	{
		// take input
		std::cin >> input;
		if (input == "end")
			break;
		for (int i = 0; i < 9; ++i)
		{
			board[i / 3][i % 3] = input[i];
		}
		if (solve(board))
			std::cout << "valid\n";
		else
			std::cout << "invalid\n";
		// debug
		/*
		std::cout << "is full : " << std::boolalpha << isFull(board) << '\n';
		std::cout << "X wins : " << std::boolalpha << xWins(board) << '\n';
		std::cout << "O wins : " << std::boolalpha << oWins(board) << '\n';

		auto debug = allLinesColumnsDiagonals(board);
		for (const auto &v : debug)
		{
			for (const auto &c : v)
			{
				std::cout << c;
			}
			std::cout << '\n';
		}
		*/
	}
}
