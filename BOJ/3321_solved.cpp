/*
	가장 큰 직사각형.

	놀랍게도 이전에 풀었던 히스토그램 문제와 관련이 없음.
	ㅠㅠ...
	핵심은 정렬 상태를 유지하며 update하는 것. O(M)으로 성취해야 함.

	풀이는 다음과 같음
	whereIs 테이블을 이용하여 grid의 position과 sorted 내의 위치를 매핑함.
	이 매핑을 유지하면서 erase되는 block과 update되는 block, 새로 등장하는block
	을 관리해야 함.

	platinum 2. O(MN)
*/
/*
#include <iostream>
#include <vector>
#include <string>

using  Block = std::pair<int, int>;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, M, result = 0;
	std::cin >> N >> M;
	std::vector<std::vector<bool>> grid(N, std::vector<bool>(M, false));
	std::vector<int> whereIs(M, -1);
	std::vector<Block> sorted;
	std::string input;
	// input
	for (int r = 0; r < N; r++)
	{
		std::cin >> input;
		for (int c = 0; c < M; ++c)
		{
			grid[r][c] = input[c] - '0';
		}
	}
	// calculate
	for (int row = 0; row < N; ++row)
	{
		std::vector<Block> nextSorted;
		// update sorted
		for (int col = 0; col < M; ++col)
		{
			if (whereIs[col] != -1 && grid[row][col])	// update
			{
				sorted[whereIs[col]].first++;
			}
			else if (whereIs[col] == -1 && grid[row][col])	// fresh
			{
				sorted.push_back(std::make_pair(1, col));
			}
			else if (whereIs[col] != -1 && !grid[row][col])	// erase
			{
				sorted[whereIs[col]].first = 0;
				whereIs[col] = -1;
			}
		}
		// push and sweeping
		for (int i = 0; i < sorted.size(); ++i)
		{
			if (sorted[i].first != 0)
			{
				// update mapping location
				whereIs[sorted[i].second] = nextSorted.size();
				// push
				nextSorted.push_back(sorted[i]);
				// sweeping
				result = std::max(result, 
					static_cast<int>(nextSorted.size()) * sorted[i].first);
			}
		}
		std::swap(sorted, nextSorted);
	}
	std::cout << result;
	return 0;
}
*/