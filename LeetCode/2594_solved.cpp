#include <iostream>
#include <vector>

#include "TreeNode.h"

using namespace std;

/*===========================================================*/

#include <algorithm>
#include <numeric>
#include <cmath>

class Solution {
private:
public:
	long long repairCars(vector<int>& ranks, int cars) {
		// 문제의 요점은 전체 차량의 수를 수리공들에게 분배하는 것이다
		// 분배를 할 때, 각 수리공마다 비용이 발생하는데, 이 비용을 최소화 하는게 목표다.

		// 시간, 즉 time을 이분탐색하면 된다.
		long long left = 0, right = 2e18;
		while (left < right)
		{
			long long const mid = (left + right) >> 1;
			if (accumulate(ranks.begin(), ranks.end(), 0LL,
				[&](long long const acc, int const r) {
					return acc + sqrt(mid / r);
				}
			) >= cars)
			{
				right = mid;
			}
			else
			{
				left = mid + 1;
			}
		}
		return left;
	}
};

