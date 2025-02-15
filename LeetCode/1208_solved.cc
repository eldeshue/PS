
#include <iostream>
#include <string>

using namespace std;

// solution
/*
	string s에서 t로 변환하는데, 그 비용이 최대 maxCost
	s에서 t로 maxcost 내로 변환 가능한 substring의 최대 길이를 구하기.
		-> two pointer

	fast와 slow의 두 포인터를 이용,
	substring의 cost를 업데이트, maxCost이하의 경우에 대해서 max substring len을 구해나감.
*/
class Solution
{
public:
	// solution method
	int equalSubstring(string s, string t, int maxCost)
	{
		const int maxLen = s.size();
		int slow = 0, fast = 0, curCost = 0, result = 0;
		for (int i = 0; i < maxLen; ++i)
		{
			s[i] = abs(s[i] - t[i]);
		}
		for (; fast < maxLen; ++fast)
		{
			while (curCost + s[fast] > maxCost)
			{
				curCost -= s[slow];
				slow++;
			}
			curCost += s[fast];
			result = max(result, fast - slow + 1);
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
