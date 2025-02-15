

#include <iostream>
#include <vector>

using namespace std;

// solution class

//#pragma GCC optimize("03")
//#pragma GCC target("avx")
//#pragma GCC target("-fsplit-loops")

class Solution
{
public:
	// solution method
	vector<int> minOperations(string boxes) {
		const int N = boxes.size();

		vector<int> prefixSum(N, 0);
		vector<int> result(N, 0);
		prefixSum[0] = boxes[0] - '0';
		for (int i = 1; i < N; ++i)
		{
			prefixSum[i] = prefixSum[i - 1];
			if (boxes[i] > '0')
			{
				prefixSum[i]++;
				result[0] += i;
			}
		}
		// 직전 위치를 기준으로
		// left count 만큼 늘리고, 
		// right count 만큼 줄인다.
		for (int i = 1; i < N; ++i)
		{
			result[i] = result[i - 1]
				+ prefixSum[i - 1]	// left count
				- (prefixSum[N - 1] - prefixSum[i - 1]);	// right count
		}
		return result;
	}
	//
};
auto _ = []()
	{
		ios_base::sync_with_stdio(false);
		cin.tie(NULL), cout.tie(NULL);
		return 0;
	}();
	// solution class

	int main()
	{
		ios_base::sync_with_stdio(false);
		cin.tie(nullptr);
		cout.tie(nullptr);

		Solution test;
	}
