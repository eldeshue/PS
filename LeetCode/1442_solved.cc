

#include <iostream>
#include <vector>

using namespace std;

// solution
class Solution
{
public:
	// solution method
	int countTriplets(vector<int> &arr)
	{
		int result;
		for (int start = 0; start < arr.size() - 1; ++start)
		{
			for (int end = 0; end < arr.size(); ++end) // included
			{
				int left = 0;
				int right = 0;
				for (int i = start; i <= end; ++i)
				{
					right ^= arr[i];
				}
				for (int mid = start + 1; mid < end; ++mid)
				{
					left ^= arr[mid];
					right ^= arr[mid];
					if (left == right)
					{
						result++;
					}
				}
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
