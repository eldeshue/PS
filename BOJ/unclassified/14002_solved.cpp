// LIS, using bitset to track the subsequence.
#include <iostream>
#include <algorithm>
#include <bitset>
#include <vector>

int N;
int buffer[1000];
std::vector<int> cache1;	// cache1[length] = final value(max value)
std::vector<std::bitset<1000>> cache2;	// cache2[length] = bitset of subsequence.

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> N;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> buffer[i];
	}

	cache1.push_back(0);	// index = 0
	cache2.push_back(std::bitset<1000>());
	cache1.push_back(buffer[0]);	// index = 1
	cache2.push_back(cache2.back());
	cache2.back().set(0, true);
	for (int i = 1; i < N; ++i)
	{
		if (cache1.back() < buffer[i]) // append LIS
		{
			cache1.push_back(buffer[i]);
			cache2.push_back(cache2.back());
			cache2.back().set(i, true);
		}
		else // update LIS
		{
			int tempPos = std::lower_bound(cache1.begin(), cache1.end(), buffer[i]) - cache1.begin();
			cache1[tempPos] = buffer[i];
			cache2[tempPos] = cache2[tempPos - 1];
			cache2[tempPos].set(i, true);
		}
	}

	// decode cache2, LIS
	int pos = 0, cnt = 0, length = cache2.size() - 1;
	std::cout << length << "\n";
	while(cnt < length)
	{
		if (cache2.back()[pos])
		{
			std::cout << buffer[pos] << " ";
			cnt++;
		}
		pos++;
	}
}