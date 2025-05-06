
#include <iostream>
#include <vector>
#include <algorithm>

using ll = long long;

void BruteForce(std::vector<ll>& result, std::vector<int> const& buffer, ll const curSum, int const curIdx)
{
	if (curIdx == buffer.size())	// base case
	{
		result.push_back(curSum);
		return;
	}
	BruteForce(result, buffer, curSum, curIdx + 1);
	if ((curSum + buffer[curIdx]) <= 1e9)
		BruteForce(result, buffer, curSum + buffer[curIdx], curIdx + 1);
	return;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, C;
	std::cin >> N >> C;
	std::vector<int> lBuffer(N / 2), rBuffer(N - N / 2);
	for (auto& l : lBuffer) std::cin >> l;
	for (auto& r : rBuffer) std::cin >> r;

	// fill
	std::vector<ll> lSum, rSum;
	BruteForce(lSum, lBuffer, 0, 0);
	BruteForce(rSum, rBuffer, 0, 0);

	// search result
	int result = 0;
	std::sort(rSum.begin(), rSum.end());
	for (auto const l : lSum)
	{
		auto itr = std::upper_bound(rSum.begin(), rSum.end(), C - l);
		result += std::distance(rSum.begin(), itr);
	}
	std::cout << result;
}
