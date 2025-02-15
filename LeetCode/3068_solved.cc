
#include <iostream>
#include <vector>

using namespace std;

// solution
/*
	문제의 상황은 단일 연결요소

	연결요소 내 임의의 두 개의 노드를 고르면, 두 노드 사이의 노드는 변화시키지 않고, 양 끝의 두 노드만 xor할 수 있다.
	이는 두 노드 사이에 존재하는 모든 에지를 선택하는 것으로 가능하다.

	따라서 위의 성질을 이용하면, 문제의 답은 sum이 최대가 되도록 하는 짝수개의 node를 선택하여 xor하는 것이다.
	즉 문제는 greedy로 변한다.

	xor을 하는 것과 안하는 것의 gap이 큰 순서로 내림차순 정렬을 하고,
	sum이 최대가 되도록 짝수개 노드를 선택한다.
*/
#include <algorithm>
using ll = long long;
class Solution
{
private:
	struct CmpXorK
	{
		int k;
		bool operator()(const int &n1, const int &n2)
		{
			return ((n1 ^ k) - n1) > ((n2 ^ k) - n2); // gap이 큰 순서로 내림차순 정렬
		}
		CmpXorK(int k) : k(k) {}
	};

public:
	// solution method
	long long maximumValueSum(vector<int> &nums, int k, vector<vector<int>> &edges)
	{
		long long sum = 0;
		std::sort(nums.begin(), nums.end(), CmpXorK(k));
		int i;
		for (i = 0; i < nums.size(); i += 2)
		{
			if (i == nums.size() - 1) // 예외처리
				break;
			long long xorSum = (nums[i] ^ k) + (nums[i + 1] ^ k);
			long long normSum = nums[i] + nums[i + 1];
			if (xorSum > normSum) // xor한 sum이 더 큰 동안 더함
				sum += xorSum;
			else // xor안하는게 더 큼, 루프 이탈
				break;
		}
		for (; i < nums.size(); ++i) // 나머지는 xor하지 않음
		{
			sum += nums[i];
		}
		return sum;
	}
};

//

// test
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;
}
