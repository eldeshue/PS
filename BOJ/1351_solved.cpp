
#include <iostream>
#include <map>

long long int N, P, Q; // N <= 10 ^ 12, 배열을 선언할 수 없음
std::map<long long int, long long int> cache;

long long int DP(long long int curVal)
{
	if (cache.find(curVal) != cache.end())	// base + cache hit
	{
		return cache[curVal];
	}
	else	// cache miss
	{
		long long int temp = DP(curVal / P) + DP(curVal / Q);
		cache.insert(std::make_pair(curVal, temp));
		return temp;
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	cache.insert(std::make_pair(0, 1));

	std::cin >> N >> P >> Q;
	std::cout << DP(N);
}