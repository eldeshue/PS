
#include <iostream>
#include <string>

using namespace std;

// solution class
#include <vector>

class Solution
{
private:
	int ringSize;
	int getMinDist(int prevPos, int curPos)
	{
		return min(abs(curPos - prevPos)
			, abs(ringSize - max(curPos, prevPos)
					+ min(curPos, prevPos)));
	}
public:
	// solution method
	int findRotateSteps(string ring, string key)
	{
		ringSize = ring.size();
		vector<int> cache1(ringSize, 2e9);
		vector<int> cache2(ringSize, 2e9);
		vector<int>& curCache = cache1;
		vector<int>& prevCache = cache2;

		for (int pos = 0; pos < ringSize; ++pos)
		{
			if (ring[pos] == key[0])
			{
				prevCache[pos] = getMinDist(0, pos) + 1;
			}
		}
		for (int curK = 1; curK < key.size(); ++curK)
		{
			fill(curCache.begin(), curCache.end(), 2e9);
			for (int curPos = 0; curPos < ringSize; ++curPos)
			{
				if (ring[curPos] == key[curK])
				{
					for (int prevPos = 0; prevPos < ringSize; ++prevPos)
					{
						if (prevCache[prevPos] != 2e9)
						{
							curCache[curPos] = min(curCache[curPos]
								, prevCache[prevPos]
								+ getMinDist(prevPos, curPos) + 1);
						}
					}
				}
			}
			swap(curCache, prevCache);
		}
		int result = 2e9;
		for (int i = 0; i < ringSize; ++i)
		{
			result = min(result, prevCache[i]);
		}
		return result;
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