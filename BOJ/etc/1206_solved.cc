
#include <iostream>
#include <vector>
#include <string>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int n;
	std::cin >> n;
	std::vector<int> nums(n);
	std::string f;
	for (int i = 0; i < n; ++i)
	{
		std::cin >> f;
		f.erase(f.find('.'), 1);
		nums[i] = std::stoi(f);
	}
	int result = 1;
	for (; result < 1000; ++result)
	{
		int cnt = 0;
		for (int &n : nums)
		{
			for (int p = 0; p <= result * 10000; p += 1000)
			{
				if (p / result == n)
				{
					cnt++;
					break;
				}
			}
		}
		if (cnt == nums.size())
		{
			break;
		}
	}
	std::cout << result;
}
