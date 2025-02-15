
#include <iostream>
#include <vector>

using namespace std;

// solution class
/*
	DP, LIS ����.

	������ liS�� ���̸� ���ϴ� �����
	�ش� step���� ���� sub seq ��, ������ ���Ұ� ���ο� ���Һ��� �۰�,
	�� �� ���̰� ���� �� sub seq�� ���̸� �����ϴ� ������ ������.

	�̸� �����Ͽ� ���̰� ���� �� sub sequence�� ���ϴµ�,
	�� ������ ������ ������ ��Һ񱳿��� ������ ���ҷ� ������ ���η� �ٲ��ش�.

	�ð� ���⵵�� ���������� O(N^2)��.
*/
#include <algorithm>
#include <memory.h>

class Solution
{
private:
	int parent[1000];	// for trace back, �ڽ��� ���� ū ����� �ִ� index�� ����
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