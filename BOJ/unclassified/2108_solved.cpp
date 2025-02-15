
#include <iostream>
#include <algorithm>
#include <array>
#include <map>
#include <cmath>

std::array<int, 500000> nums;
std::map<int, int> cntTable;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, cnt = 0, f = 4000, s = 4000;
	double avg = 0;
	std::cin >> N;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> nums[i];
		avg += nums[i];
		if (cntTable.find(nums[i]) == cntTable.end())
			cntTable.insert(std::make_pair(nums[i], 1));
		else
			cntTable[nums[i]]++;
	}
	std::sort(nums.begin(), nums.begin() + N);
	std::cout << static_cast<int>(round(avg / N)) << '\n' << nums[N / 2] << '\n';
	for (const std::pair<int, int>& curEntry : cntTable)
	{
		const int& curNum = curEntry.first;
		const int& curCnt = curEntry.second;
		if (curCnt > cnt)
		{
			cnt = curCnt;
			f = curNum;
			s = 5000;
		}
		else if (cnt == curCnt && s == 5000)
		{
			s = curNum;
		}
	}
	if (s != 5000)
		std::cout << s << '\n';
	else
		std::cout << f << '\n';
	std::cout << nums[N - 1] - nums[0] << '\n';
}