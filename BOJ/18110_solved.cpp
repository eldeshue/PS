
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

long long myRound(double val)
{
	long long retVal = 10 * val;
	if ((retVal % 10) >= 5)
	{
		retVal /= 10;
		retVal++;
	}
	else
	{
		retVal /= 10;
	}
	return retVal;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	std::cin >> N;
	std::vector<long long> num(N);
	for (int i = 0; i < N; ++i)
	{
		std::cin >> num[i];
	}
	std::sort(num.begin(), num.end());

	int cutNum = myRound((15.0 * static_cast<double>(N)) / 100.0);
	long long sum = 0;
	for (int i = cutNum; i < N - cutNum; ++i)
	{
		sum += num[i];
	}
	std::cout << myRound(static_cast<double>(sum) / static_cast<double>(N - 2 * cutNum));
}