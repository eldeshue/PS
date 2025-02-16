#include <iostream>
#include <vector>

using namespace std;

#include <functional>
class Solution {
private:
public:
	vector<int> constructDistancedSequence(int n) {
		int const N = 2 * n - 1;
		vector<int> result(N, 0);
		vector<bool> curNums(n + 1, false);
		function<bool(int const)> backTrack = [&](int const pos) {
			if (pos == N)
				return true;
			else if (result[pos] != 0)
				return backTrack(pos + 1);
			else
			{
				bool isFound = false;
				for (int num = n; num > 1; --num)
				{
					if (!curNums[num] && (pos + num) < N && result[pos + num] == 0)
					{
						result[pos] = num;
						result[pos + num] = num;
						curNums[num] = true;
						isFound |= backTrack(pos + 1);
						if (isFound)
							break;
						result[pos] = 0;
						result[pos + num] = 0;
						curNums[num] = false;
					}
				}
				if (!isFound && !curNums[1])
				{
					result[pos] = 1;
					curNums[1] = true;
					isFound |= backTrack(pos + 1);
					if (isFound)
						return isFound;
					result[pos] = 0;
					curNums[1] = false;
				}
				return isFound;
			}
			};
		backTrack(0);	// always an answer
		return result;
	}
};