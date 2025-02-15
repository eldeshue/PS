// 2진 탐색 문제
// 다만, 구현에 있어서 상당한 문제.
// 외워야 하는가?
/*
#include <iostream>
#include <algorithm>
#include <vector>

int N, M;
std::vector<int> trees;

bool is_ok(int H)
{
	long long total_len = 0;
	for (int i = N - 1; i >= 0; --i)
	{
		if (trees[i] <= H)
			break;
		total_len += trees[i] - H;
	}
	return (total_len >= M);
}

int binary_search(int low, int high)
{
	if (low == high)
		return high;
	int mid = (low + high + 1) >> 1;
	if (is_ok(mid))
		return  binary_search(mid, high);
	else
		return binary_search(low, mid - 1);
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int input;
	std::cin >> N >> M;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> input;
		trees.push_back(input);
	}
	std::sort(trees.begin(), trees.end());
	std::cout << binary_search(-1, trees[N - 1]);
}
*/