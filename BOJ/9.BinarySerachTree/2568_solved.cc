
#include <iostream>
#include <algorithm>
#include <vector>

using pii = std::pair<int, int>;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	int N;
	std::cin >> N;
	std::vector<pii> pairs(N);
	for (auto &p : pairs)
		std::cin >> p.first >> p.second;
	// sorting
	std::sort(pairs.begin(), pairs.end());
	std::transform(pairs.begin(), pairs.end(), pairs.begin(), [](const pii &p)
				   { return std::make_pair(p.second, p.first); });
	// lis
	// save prev position to trace back.
	// per dist, min value, {value, original idx}
	std::vector<int> parents(N, -1);
	std::vector<pii> minValPerLen(N, {2e9, -1});
	minValPerLen[0] = {0, -1};
	for (int i = 0; i < N; ++i)
	{
		auto [curVal, ___] = pairs[i];
		// binary serach
		auto targetPos = std::lower_bound(minValPerLen.begin(), minValPerLen.end(), std::make_pair(curVal, -1));
		auto &[minVal, minIdx] = *targetPos;
		if (curVal < minVal)
		{
			minVal = curVal;
			minIdx = i;
			// save index
			if (targetPos != minValPerLen.begin())
			{
				auto prevPos = targetPos - 1;
				const int prevIdx = prevPos->second;
				// where is prev Index?
				parents[i] = prevIdx;
			}
		}
	}

	// trace back and erase unused
	int maxLen = 0;
	int targetIdx = -1;
	for (int i = N - 1; i >= 0; --i)
	{
		if (minValPerLen[i].first != 2e9)
		{
			maxLen = i;
			targetIdx = minValPerLen[i].second;
			break;
		}
	}
	while (targetIdx != -1)
	{
		// erase used idx
		pairs[targetIdx].second = -1;
		targetIdx = parents[targetIdx];
	}
	// print result
	std::cout << N - maxLen << '\n';
	for (const auto &[___, n] : pairs)
	{
		if (n != -1)
			std::cout << n << '\n';
	}
}
