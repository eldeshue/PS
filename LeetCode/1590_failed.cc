

#include <iostream>
#include <vector>

using namespace std;

/*
#pragma GCC optimize("03")
#pragma GCC target("avx")
#pragma GCC target("-fsplit-loops")
*/

#include <algorithm>
class Solution
{
private:
	using ll = long long;
	using pii = pair<ll, ll>;

public:
	// solution method
	int minSubarray(vector<int> &nums, int p)
	{
		// prefix array
		const int N = nums.size();
		vector<pii> prefixSum(N + 1, {0, 0});
		for (int i = 0; i < N; ++i)
			prefixSum[i + 1] = make_pair(prefixSum[i].first + nums[i], i + 1);
		const int offset = prefixSum[N].first % p;
		if (prefixSum[N].first < p)
			return -1;
		if (offset == 0)
			return 0;
		// prefix array를 나머지를 기준으로 먼저 정렬하고, 이후 크기순으로 정렬함
		// 정렬된 prefix array를 순회하면서 나머지를 기준으로 하는 partition을 만들고
		sort(prefixSum.begin(), prefixSum.end(), [p](const pii &p1, const pii &p2) -> bool
			 {
				if ((p1.first % p) == (p2.first % p))
					return p1.first < p2.first;
				return (p1.first % p) < (p2.first % p); });
		// get range of partition
		for (int i = 0; i <= N; ++i)
			std::cout << prefixSum[i].first << ' ';
		std::cout << '\n';
		vector<pii> rangeByMod(p, {-1, -1});
		rangeByMod[0].first = 0;
		for (int i = 1; i < prefixSum.size(); ++i)
		{
			const int curMod = prefixSum[i].first % p;
			if ((prefixSum[i - 1].first % p) != curMod)
				rangeByMod[curMod].first = i;
			rangeByMod[curMod].second = std::max(rangeByMod[curMod].second, 1LL + i);
		}
		// 각 원소마다 자신의 나머지(x)와 그 짝이 되는 나머지값((x + offset) % p)을 바탕으로 자신의 상대가 되는 partition을 찾음.
		ll result = N;
		for (int i = 0; i < N + 1; ++i)
		{
			const ll curVal = prefixSum[i].first;
			const ll curMod = prefixSum[i].first % p;
			const ll opponantMod = (curMod + offset) % p;
			// 탐색할 partition의 range 획득
			const auto rangeStart = prefixSum.begin() + rangeByMod[opponantMod].first;
			const auto rangeEnd = prefixSum.begin() + rangeByMod[opponantMod].second;
			if (rangeStart == rangeEnd)
				continue;
			// lower bound
			// 상대 파티션 내부를 이진탐색하여, 자신보다 큰 상대 원소를 획득할것.
			std::vector<pii>::iterator itr = std::lower_bound(rangeStart, rangeEnd, make_pair(curVal, 0LL));
			// 탐색 성공 시, 즉 가리키는 iterator가 end가 아니라면, subarray length 업데이트
			if (itr != rangeEnd && itr->second > prefixSum[i].second)
			{
				std::cout << curVal << ' ' << itr->first << '\n';
				result = std::min(result, (itr->second - prefixSum[i].second));
			}
		}
		if (result == N)
			return -1;
		return result;
	}
};

// test
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	vector<int> input = {6, 3, 5, 2};
	Solution test;
	std::cout << test.minSubarray(input, 9);
}
