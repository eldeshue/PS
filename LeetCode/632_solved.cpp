
#include <iostream>
#include <vector>

using namespace std;

// solution class

//#pragma GCC optimize("03")
//#pragma GCC target("avx")
//#pragma GCC target("-fsplit-loops")
#include <algorithm>
class Solution
{
private:
	using Item = pair<int, int>;	// value, list num
public:
	// solution method, two pointer
	vector<int> smallestRange(vector<vector<int>>& nums)
	{
		const int K = nums.size();
		std::vector<int> freq(K);
		for (int i = 0; i < K; ++i)
			freq[i] = nums[i].size();
		std::vector<Item> items;
		for (int listNum = 0; listNum < K; ++listNum)
			for (const int value : nums[listNum])
				items.push_back(make_pair(value, listNum));
		// sort
		sort(items.begin(), items.end());
		// two pointer
		vector<int> itemCnt(K, 0);
		int listCnt = 0;
		int left = 0;	// index of items, two pointer
		int rStart = -1, rEnd = 2e9;// result
		for (const auto& [cEnd, lIdx] : items) // move right
		{
			// update status
			itemCnt[lIdx]++;
			if (itemCnt[lIdx] == 1)
				listCnt++;
			while (listCnt == K)
			{
				// update right
				const int cStart = items[left].first;
				// update result
				if ((rEnd - rStart) > (cEnd - cStart))
				{
					rStart = cStart;
					rEnd = cEnd;
				}
				// move left 
				itemCnt[items[left].second]--;
				if (itemCnt[items[left].second] == 0)
					listCnt--;
				left++;
			}
		}
		return vector<int>{rStart, rEnd};
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
	auto input = vector<vector<int>>(1, { 1 });
	test.smallestRange(input);
}

