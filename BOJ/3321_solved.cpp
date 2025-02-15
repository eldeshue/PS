/*
	���� ū ���簢��.

	����Ե� ������ Ǯ���� ������׷� ������ ������ ����.
	�Ф�...
	�ٽ��� ���� ���¸� �����ϸ� update�ϴ� ��. O(M)���� �����ؾ� ��.

	Ǯ�̴� ������ ����
	whereIs ���̺��� �̿��Ͽ� grid�� position�� sorted ���� ��ġ�� ������.
	�� ������ �����ϸ鼭 erase�Ǵ� block�� update�Ǵ� block, ���� �����ϴ�block
	�� �����ؾ� ��.

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