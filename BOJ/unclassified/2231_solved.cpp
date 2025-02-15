
#include <iostream>
#include <deque>

int N, len;
std::deque<int> status;

int recurse(int pos)
{
	int result = 0;
	if (pos == len)
	{
		int divideSum = 0;
		int radix = 1;
		for (int i = pos - 1; i >= 0; --i)
		{
			divideSum += status[i] + status[i] * radix;
			result += status[i] * radix;
			radix *= 10;
		}
		if (divideSum == N)
			return result;
		return 0;
	}
	for (int i = 0; i < 10; ++i)
	{
		// deque push_back
		status.push_back(i);
		// search next
		result = recurse(pos + 1);
		if (result > 0)
			break;
		// pop back
		status.pop_back();
	}
	return result;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> N;
	len = 1;
	int divider = 1;
	while (N / divider >= 10)
	{
		divider *= 10;
		len++;
	}
	std::cout << recurse(0);
}