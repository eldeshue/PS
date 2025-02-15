
#include <iostream>
#include <vector>
#include <unordered_set>
#include <functional>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	int N;
	std::cin >> N;
	std::vector<std::vector<int>> matrix(N, std::vector<int>(N));
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			std::cin >> matrix[i][j];

	// back tracking
	std::unordered_set<int> start, link;
	int result = 2e9, startSum = 0, linkSum = 0;
	std::function<void(int)> backTrack = [&](int curPeople) {
		if (curPeople == N)
		{
			result = std::min(result, std::abs(startSum - linkSum));
			return;
		}

		// pick start
		if (start.size() < (N / 2))
		{
			// add start sum
			int sum = 0;
			for (int const n : start)
				sum += matrix[n][curPeople] + matrix[curPeople][n];
			startSum += sum;
			start.insert(curPeople);
			backTrack(curPeople + 1);
			startSum -= sum;
			start.erase(curPeople);
		}

		// pick link
		if (link.size() < (N / 2))
		{
			// add link sum
			int sum = 0;
			for (int const n : link)
				sum += matrix[n][curPeople] + matrix[curPeople][n];
			linkSum += sum;
			link.insert(curPeople);
			backTrack(curPeople + 1);
			linkSum -= sum;
			link.erase(curPeople);
		}

		return;
		};

	// calculate and print
	backTrack(0);
	std::cout << result;
}
