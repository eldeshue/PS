
#include <iostream>
#include <vector>

using namespace std;

// solution
#pragma GCC optimize("03")
#pragma GCC target ("avx")
#include <algorithm>
#include <set>

/*
    total result : O(N (K + log n) )
*/
class Solution
{
private:
	int N;
public:
	double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int k)
	{
		N = quality.size();
		vector<pair<double, double>> wPerQ(N);
		multiset<int, less<int>> availableQuality;
		double result = 2e9;

		for (int i = 0; i < N; ++i)
			wPerQ[i] = make_pair(static_cast<double>(wage[i]) / static_cast<double>(quality[i]), quality[i]);
		sort(wPerQ.begin(), wPerQ.end());
		for (int maxPos = 0; maxPos < N; ++maxPos)	// both closed range, O(N)
		{
			if (availableQuality.size() >= k - 1)
			{
				double qSum = wPerQ[maxPos].second;
				int i = 0;
                // O(K)
				for (auto iter = availableQuality.begin(); i < k - 1; ++i, iter++)
				{
					qSum += *(iter);
				}
				result = min(result,
					qSum * wPerQ[maxPos].first);
			}
			availableQuality.insert(wPerQ[maxPos].second);  // log n
		}
		return result;
    }
};
//

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;

}
