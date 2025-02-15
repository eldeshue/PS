
/*
	주어진 정수 배열을 다음과 같이 재배열해서 제출하기.

	1. 부호가 번갈아 등장함. 시작 원소는

	2. 같은 부호 끼리는 기존의 순서가 유지되어야 함(stable)



*/

#include <iostream>
#include <vector>

using namespace std;

// solution
class Solution
{
public:
	// solution method
	vector<int> rearrangeArray(vector<int> &nums)
	{
		vector<int> result(nums.size(), 0);

		int even_idx = 0, odd_idx = 1;
		for (const int &n : nums)
		{
			if (n < 0)
			{
				result[odd_idx] = n;
				odd_idx += 2;
			}
			else
			{
				result[even_idx] = n;
				even_idx += 2;
			}
		}
		return result;
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
