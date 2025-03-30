
#include <iostream>
#include <queue>
#include <vector>

// total N log N

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	int N;
	std::cin >> N;
	std::vector<std::vector<int>> grid(N, std::vector<int>(N, 0));
	for (auto& row : grid)
		for (auto& n : row)
			std::cin >> n;

	// priority queue
	using pii = std::pair<int, int>;
	std::priority_queue<pii, std::vector<pii>, std::less<pii>> pq;
	std::vector<int> rowPointer(N, N - 2);
	for (int col = 0; col < N; ++col)	// O(N)
		pq.push(std::make_pair(grid[N - 1][col], col));	// O(log N)

	// partial sort
	for (int i = 1; i < N; ++i)	// O(N)
	{
		auto const [val, colNum] = pq.top();
		pq.pop();

		if (rowPointer[colNum] >= 0)
		{
			// O(log N)
			pq.push(std::make_pair(grid[rowPointer[colNum]--][colNum], colNum));
		}
	}

	// print result
	std::cout << pq.top().first;
}