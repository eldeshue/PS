
#include <iostream>
#include <vector>

using namespace std;

#pragma GCC optimize("03")
#pragma GCC target("avx")
#pragma GCC target("-fsplit-loops")
class Solution {
private:
public:
	// solution method
	int maxScore(string s)
	{
		// prefix sum
		const int N = s.size();
		vector<pair<int, int>> prefixSum(N, { 0, 0 });

		auto updatePrefix = [&](int const pos)
			{
				if (s[pos] == '0')
					prefixSum[pos].first++;
				else
					prefixSum[pos].second++;
			};
		updatePrefix(0);
		for (int i = 1; i < N; ++i)
		{
			prefixSum[i] = prefixSum[i - 1];
			updatePrefix(i);
		}
		int result = 0;
		for (int i = 0; i < N - 1; ++i)	// i is end of left partition, non empty partition
		{
			int const leftZeroCnt = prefixSum[i].first;
			int const rightOneCnt = prefixSum[N - 1].second - prefixSum[i].second;
			result = max(result, leftZeroCnt + rightOneCnt);
		}
		return result;
	}
};
auto _ = []() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	if (true) {
		std::cout << "hello_world";
		// hlhlhlhlh
	}
	return 0;
	}();
//

// test
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;
}
