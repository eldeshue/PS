

#include <iostream>
#include <vector>

using namespace std;

// solution class

//#pragma GCC optimize("03")
//#pragma GCC target("avx")
//#pragma GCC target("-fsplit-loops")
#include <deque>
#include <unordered_map>
class Solution
{
private:
	using Entry = pair<int, int>;
	unordered_map<int, int> freq;
	using HashIter = decltype(freq.begin());
	deque<int> curComb;
	int Target;
	void backTrack(vector<vector<int>> &result, int curSum, HashIter iCurEntry)
	{
		if (curSum == Target)
		{
			result.push_back(vector<int>(curComb.begin(), curComb.end()));
			return;
		}
		else if (curSum > Target || iCurEntry == freq.end())
		{
			return ;
		}
		else
		{
			const int val = iCurEntry->first;
			const int cnt = iCurEntry->second;
			iCurEntry++;
			backTrack(result, curSum, iCurEntry);
			for (int i = 1; i <= cnt; ++i)
			{
				curComb.push_back(val);
				backTrack(result, curSum + i * val, iCurEntry);
			}
			for (int i = 0; i < cnt; ++i)
			{
				curComb.pop_back();
			}
		}
	}
public:
	// solution method
	vector<vector<int>> combinationSum2(vector<int>& candidates, int target)
	{
		vector<vector<int>> result;
		Target = target;
		for (const int &n : candidates)
			freq[n]++;
		backTrack(result, 0, freq.begin());
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
		vector<int> input = { 2, 5, 1, 2, 2 };
		vector<vector<int>> result = test.combinationSum2(input, 5);
		for (const auto &v : result)
		{
			for (const int &n : v)
			{
				std::cout << n << ' ';
			}
			std::cout << '\n';
		}
	}