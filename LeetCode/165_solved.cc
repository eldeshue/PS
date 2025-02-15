
#include <iostream>
#include <string>

using namespace std;

// solution
class Solution
{
private:
	int updateRevSum(int &revSum, const int &startIdx, const string &version)
	{
		revSum = 0;
		for (int i = startIdx; i < version.size(); ++i)
		{
			if (version[i] == '.')
			{
				return ++i;
			}
			revSum *= 10;
			revSum += version[i] - '0';
		}
		return version.size();
	};

public:
	// solution method
	int compareVersion(string version1, string version2)
	{
		int idx1 = 0, idx2 = 0, revSum1 = 0, revSum2 = 0;
		bool flag1 = true, flag2 = true;
		while (true) // revision
		{
			// range check
			if (idx1 == version1.size() && idx2 == version2.size())
			{
				break;
			}
			// version 1
			idx1 = updateRevSum(revSum1, idx1, version1);
			// version 2
			idx2 = updateRevSum(revSum2, idx2, version2);
			// evaluate
			if (revSum1 > revSum2)
				return 1;
			else if (revSum1 < revSum2)
				return -1;
			else // equal
				continue;
		}
		return 0;
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
