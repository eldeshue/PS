
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>

int N, M;
std::vector<int> nums;
std::set<std::vector<int>> result;

void DFS(std::vector<int> vec, int statusBit, int pos)
{
	if (pos == M)
	{
		result.insert(vec);
		return;
	}

	vec.push_back(0);
	for (int i = 0; i < N; ++i)
	{
		if ((statusBit & (1 << i)) == 0)
		{
			vec.back() = nums[i];
			DFS(vec, statusBit | (1 << i), pos + 1);
		}
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> N >> M;
	nums.resize(N);
	for (int i = 0; i < N; ++i)
	{
		std::cin >> nums[i];
	}
	std::sort(nums.begin(), nums.end(), std::less<void>());
	DFS(std::vector<int>(), 0, 0);
	for(const auto& v : result)
	{
		for (const auto& num : v)
		{
			std::cout << num << " ";
		}
		std::cout << "\n";
	}
}