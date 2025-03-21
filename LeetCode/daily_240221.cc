
#include <iostream>

using namespace std;

// solution

class Solution
{
public:
	Solution()
	{
		ios_base::sync_with_stdio(false);
		cin.tie(nullptr);
		cout.tie(nullptr);
	}
	int rangeBitwiseAnd(int left, int right)
	{
		int result = 0;
		for (int i = 30; i >= 0; --i)
		{
			if ((left >> i) != (right >> i))
				break;
			result |= (1 << i) & left;
		}
		return result;
	}
};

// solution

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;
	int l, r;
	l = 5, r = 7;
	std::cout << test.rangeBitwiseAnd(l, r) << '\n';
	l = 0, r = 0;
	std::cout << test.rangeBitwiseAnd(l, r) << '\n';
	l = 1, r = 2147483647;
	std::cout << test.rangeBitwiseAnd(l, r) << '\n';
}
