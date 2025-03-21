
#include <iostream>
#include <vector>
#include <unordered_map>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	long long T, n, m;
	std::cin >> T >> n;
	std::vector<long long> a(n);
	for (long long i = 0; i < n; ++i)
		std::cin >> a[i];
	std::cin >> m;
	std::vector<long long> b(m);
	for (long long i = 0; i < m; ++i)
		std::cin >> b[i];
	std::unordered_map<long long, long long> cache;
	for (long long start = 0; start < n; ++start)
	{
		long long sum = 0;
		for (long long end = start; end < n; ++end)
		{
			sum += a[end];
			if (cache.find(sum) == cache.end())
				cache.insert(std::make_pair(sum, 0));
			cache[sum]++;
		}
	}
	long long result = 0;
	for (long long start = 0; start < m; ++start)
	{
		long long sum = 0;
		for (long long end = start; end < m; ++end)
		{
			sum += b[end];
			if (cache.find(T - sum) != cache.end())
				result += cache[T - sum];
		}
	}
	std::cout << result;
}
