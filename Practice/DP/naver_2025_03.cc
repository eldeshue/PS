
#include <iostream>
#include <array>
#include <vector>
#include <numeric>
#include <algorithm>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	constexpr int const MAX_SIZE = 1 << 20;
	std::array<bool, MAX_SIZE> cache;
	std::fill(cache.begin(), cache.end(), false);

	int N;
	std::cin >> N;
	std::vector<std::string> input(N);
	for (auto& n : input)
		std::cin >> n;

	std::vector<int> tastes(N);
	std::transform(input.begin(), input.end(), tastes.begin(), [](std::string const& str) {
		int result = 0;
		for (int i = 0; i < str.size(); ++i)
		{
			result |= (!!(str[str.size() - 1 - i] - '0') << i);
		}
		return result;
		});

	for (auto const n : tastes)
	{
		for (int i = 0; i < MAX_SIZE; ++i)
		{
			if (cache[i])
			{
				cache[i | n] = true;
			}
		}
		cache[n] = true;
	}
	std::cout << std::accumulate(cache.begin(), cache.end(), 0);
}

/*
// yechakim's solution by js
// * ['0010','0110', '1010']
function solution(fruits){
	const flavors =fruits.map(i=>parseInt(i, 2));
	const cache = Array.from({length: 2 ** fruits[0].lenth }).fill(0);
	for(const flavor of flavors){
		cache.forEach((c, i)=>{
			if(c){
				cache[i | flavor] = true;
			}
		});
		cache[flavor] = true
	}
	return cache.filter(f => f).length;
}
*/
