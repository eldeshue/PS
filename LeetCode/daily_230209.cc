
/*
	가장 긴 나눠지는 수들의 부분집합.

	부분집합을 구성하는 임의의 두 수는 하나가 다른 하나의 약수임을 보장한다.
	트리를 구성하면 빠르게 찾을 수 있지 않을까?

*/
#include <iostream>
#include <vector>

using namespace std;

// solution
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <stack>

class Solution
{
public:
	vector<int> largestDivisibleSubset(vector<int>& nums)
	{
	}
};

// solution

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;
	vector<int> nums = {1, 2, 4, 8};
	vector<int> result = test.largestDivisibleSubset(nums);
	for (const int& n : result)
	{
		std::cout << n << ' ';
	}
}
