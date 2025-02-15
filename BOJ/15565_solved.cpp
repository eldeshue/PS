
#include <iostream>
#include <bitset>

using uint = unsigned int;
std::bitset<1000000> dolls;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, K, start = 0, end = 0;
	uint cnt = 0, result = -1;
	std::cin >> N >> K;
	for (uint i = 0; i < N; ++i)
	{
		std::cin >> start;
		dolls[i] = 1 & start;
	}
	start = 0;
	while (end != N)
	{
		while (cnt < K && end < N)
			cnt += dolls[end++];
		while (!dolls[start] && start < N)
			start++;
		if (cnt < K)
			break;
		result = std::min(result, static_cast<uint>(end - start));
		start++; cnt--;
	}
	std::cout << static_cast<int>(result);
}