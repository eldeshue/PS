
#include <iostream>
#include <vector>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	auto getD = [](int n)->int
		{
			int sum = n;

			while (n > 0)
			{
				sum += n % 10;
				n /= 10;
			}
			return sum;
		};
	std::vector<bool> isSelfNum(10001, true);

	for (int start = 1; start < 10000; ++start)
	{
		if (isSelfNum[start])
		{
			int curNum = start;
			while (true)
			{
				curNum = getD(curNum);
				if (curNum > 10000)
					break;
				else
					isSelfNum[curNum] = false;
			}
		}
	}

	for (int i = 1; i <= 10000; ++i)
	{
		if (isSelfNum[i])
			std::cout << i << '\n';
	}
}