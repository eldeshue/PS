
#include <iostream>
#include <vector>

using namespace std;

#pragma GCC optimize("03")
#pragma GCC target("avx")
#pragma GCC target("-fsplit-loops")
#include <numeric>
class Solution
{
private:
public:
	// solution method
	vector<int> missingRolls(vector<int> &rolls, int mean, int n)
	{
		const int m = rolls.size();
		const int totalSum = mean * (n + m);
		const int nSum = totalSum - accumulate(rolls.begin(), rolls.end(), 0);
		if (nSum > 6 * n || nSum < n)
			return {};
		vector<int> result(n, nSum / n);
		int restOfNSum = nSum % n;
		for (int &diceNum : result)
		{
			const int gap = std::min(6 - diceNum, restOfNSum);
			diceNum += gap;
			restOfNSum -= gap;
			if (restOfNSum == 0)
				break;
		}
		return result;
	}
};
auto _ = []()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	return 0;
}();
//

// test
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;
}
