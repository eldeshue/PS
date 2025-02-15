
#include <iostream>
#include <vector>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, M;
	std::cin >> N >> M;
	std::vector<int> prefixSum(N);
	std::vector<int> freq(M, 0);
	freq[0] = 1;
	for (int& n : prefixSum)
		std::cin >> n;
	int prevVal = 0;
	long long result = 0;
	for (int &n : prefixSum)
	{
		n = (n + prevVal) % M;
		result += freq[n];
		freq[n]++;
		prevVal = n;
	}
	std::cout << result;
}