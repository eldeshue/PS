
#include <iostream>
#include <vector>

using namespace std;

class Solution {
private:
	int i;
	bool isPunish(int const sum, int const target)
	{
		if (target == 0)
		{
			return (i == sum);
		}
		bool result = false;
		for (int div = 10; div <= 1000000; div *= 10)
		{
			int sub = target % div;
			result |= isPunish(sum + sub, target / div);
			if ((target / div) == 0)
				break;
		}
		return result;
	}
public:
	int punishmentNumber(int n) {
		// back tracking   
		int result = 0;
		for (i = 1; i <= n; ++i)
		{
			if (isPunish(0, i * i))
			{
				result += i * i;
			}
		}
		return result;
	}
};
