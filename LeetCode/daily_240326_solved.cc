
#include <iostream>
#include <vector>

using namespace std;

// solution
/*
	자리찾기 알고리즘.

	주어진 벡터를 조작하여 벡터 내부의 원소를 자기 자신의 인덱스와 일치시키도록 한다.
	만약 원소가 주어진 벡터의 인덱스 범위를 넘어간다면 해당 인덱스의 자리를 0으로 초기화 한다.
		-> 이는 곧 1~n 범위에서 공백이 발생함을 의미하고, 우리가 찾는 문제의 답이 존재함을 의미한다.

	만약 모든 원소가 자리를 다 찾아갔다. 이말은 주어진 벡터 안에 있는 원소가 모두 1~n임을 의미하고, 우리의 답은 n + 1이 된다.
*/
class Solution
{
public:
	// solution method
	int firstMissingPositive(vector<int> &nums)
	{
		const int n = nums.size();
		int result = -1;

		nums.push_back(0);
		// move element to it's correct position
		// if there is ccorrect position int nums, set 0
		for (int i = 0; i <= n; ++i)
		{
			if (nums[i] > n || nums[i] < 0) // out of nums range
				nums[i] = 0;
			while (nums[i] != nums[nums[i]])
			{
				swap(nums[i], nums[nums[i]]);
				if (nums[i] > n || nums[i] < 0) // out of nums range
					nums[i] = 0;
			}
		}
		// find empty position
		for (int i = 1; i <= n; ++i)
		{
			if (nums[i] != i)
			{
				result = i;
				break;
			}
		}
		// if there is no position
		if (result == -1)
			result = n + 1;
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

	vector<int> input = {1, 1000};
	Solution test;
	std::cout << test.firstMissingPositive(input);
}
