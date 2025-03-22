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
		// ������ ������ ��ü ������ ���� �������鿡�� �й��ϴ� ���̴�
		// �й踦 �� ��, �� ���������� ����� �߻��ϴµ�, �� ����� �ּ�ȭ �ϴ°� ��ǥ��.

		// �ð�, �� time�� �̺�Ž���ϸ� �ȴ�.
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

