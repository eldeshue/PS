
#include <iostream>
#include <unordered_map>

int minTime, resultHeight = 0;
std::unordered_map<int, int> land;

int getTimeToNarashi(int height, const int B)
{
	int gap, blockToRemove = 0, blockToPut = 0;
	for (const auto& entry : land)
	{
		gap = entry.first - height;
		if (gap > 0)
		{
			blockToRemove += entry.second * gap;
		}
		else
		{
			blockToPut -= entry.second * gap;
		}
	}
	// 개수 조절
	if (blockToPut <= B + blockToRemove)
	{
		return blockToPut + 2 * blockToRemove;
	}
	return 2147483647;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	minTime = 2147483647;

	int N, M, B, temp, start = 0;
	std::cin >> N >> M >> B;
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < M; ++j)
		{
			std::cin >> temp;
			land[temp]++;
			start = std::max(start, temp);
		}
	}
	for (int h = start; h >= 0; --h)
	{
		temp = getTimeToNarashi(h, B);
		if (minTime > temp)
		{
			minTime = temp;
			resultHeight = h;
		}
	}
	std::cout << minTime << ' ' << resultHeight;
}