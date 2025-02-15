
#include <iostream>
#include <vector>

using namespace std;

// solution class
/*
	DP, LIS 응용.

	기존의 liS의 길이를 구하는 방법은
	해당 step까지 구한 sub seq 중, 마지막 원소가 새로운 원소보다 작고,
	그 중 길이가 가장 긴 sub seq의 길이를 저장하는 것으로 구현됨.

	이를 응용하여 길이가 가장 긴 sub sequence를 구하는데,
	그 조건을 마지막 원소의 대소비교에서 마지막 원소로 나눠짐 여부로 바꿔준다.

	시간 복잡도는 마찬가지로 O(N^2)임.
*/
#include <algorithm>
#include <memory.h>

class Solution
{
private:
	int parent[1000];	// for trace back, 자신의 가장 큰 약수가 있는 index를 저장
	int cache[1000];	// length of the subset, end with nums[i]
public:
	// solution method
	vector<int> largestDivisibleSubset(vector<int>& nums) 
	{
		vector<int> result;
		memset(parent, -1, sizeof(parent));
		memset(cache, 0, sizeof(cache));

		// sort
		sort(nums.begin(), nums.end());
		// DP, first cannot be checked.
		cache[0] = 1;
		for (int i = 1; i < nums.size(); ++i)
		{
			cache[i] = 1;
			for (int j = 0; j < i; ++j)
			{
				if (nums[i] % nums[j] == 0
					&& cache[i] < cache[j] + 1)	// divisible and updatable
				{
					cache[i] = cache[j] + 1;
					parent[i] = j;
				}
			}
		}
		// find the longest and trace back
		int maxLen = 0;
		int curIdx = -1;
		for (int i = 0; i < nums.size(); ++i)
		{
			if (cache[i] > maxLen)
			{
				maxLen = cache[i];
				 curIdx = i;
			}
		}
		// trace back and push_back
		while (curIdx != -1)
		{
			result.push_back(nums[curIdx]);
			curIdx = parent[curIdx];
		}
		return result;
	}
};

// solution class

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	Solution test;
	vector<int> nums = { 1, 2, 3 };
	vector<int> result = test.largestDivisibleSubset(nums);
	for (const int& n : result)
	{
		std::cout << n << ' ';
	}
}