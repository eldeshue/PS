
#include <iostream>
#include <vector>

using namespace std;

// solution class
/*
	풀이 방향

	0. 핵심 변수 completeRange
	completeRange 변수는 부분합을 통해서 커버 가능한 범위를 의미함.
	이 변수의 값이 n이상이 될 때 까지 진행하고, 그 과정에 필요한 패치의 횟수를 구함.

	1. 확장의 조건
	그렇다면 해당 변수를 확장하는 조건이 중요함.
	확장하기 위한 조건은 새로이 추가되는 값이 부분합을 통해서 표현 가능한 범위여야 함.
	즉 1부터 curNum - 1까지는 모두 표현가능해야 curNum을 추가할 수 있음.

	만약 표현이 불가능한 부분이 있다면, patch를 통해서 매꿔줘야 함.
	이렇게 패치가 필요한 부분을 hole이라 한다.

	2. 패치에 대해서
	패치를 통해서 completeRange를 확장하고, 이를 통해서 curNum을 받아들일 수 있음.
	최소 횟수의 patch를 수행해야 하므로, 최소비용으로 completeRange 최대로 확장해야 함.

	한 번의 패치로 최대의 확장을 얻는 방법은 completeRange + 1을 추가하는 것임.
	왜냐하면 이미 1부터 completeRange까지는 완벽하게 cover하고 있기 때문임.
*/
class Solution
{
public:
	// solution method
	int minPatches(vector<int>& nums, int n)
	{
		long long completeRange = 0;
		int numPatch = 0;
		for (const int& curNum : nums)
		{
			// if there is a whole between current range and added number, add patch.
			while (completeRange < curNum - 1 && completeRange < n)
			{
				// setting patch
				// patched number will be (completeRange + 1)
				numPatch++;
				completeRange = 2 * completeRange + 1;
			}
			completeRange += curNum;
			if (completeRange >= n)
				break;
		}
		// after all, still there is a whole,
		// add patches
		while (completeRange < n)
		{
			numPatch++;
			completeRange = 2 * completeRange + 1;
		}
		return numPatch;
	}
	//
};

// solution class

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;

}

