

#include <iostream>
#include <vector>

using namespace std;

// solution class

//#pragma GCC optimize("03")
//#pragma GCC target("avx")
//#pragma GCC target("-fsplit-loops")
#include <numeric>
class Solution
{
public:
	// solution method
	int minExtraChar(string s, vector<string>& dictionary)
	{
		vector<int> cache(s.size());

		iota(cache.begin(), cache.end(), 1);
		for (int pos = 0; pos < s.size(); ++pos)	// 1D dp, tiling problem
		{
			for (const auto& tile : dictionary)
			{
				const int tileSize = tile.size();
				if ((pos - 1 + tileSize) < s.size())
				{
					if (s.find(tile, pos) == pos)	// match found
					{
						if (pos == 0)	// exception, -1
						{
							cache[pos - 1 + tileSize]
								= min(cache[pos - 1 + tileSize], 0);
						}
						else
						{
							cache[pos - 1 + tileSize]
								= min(cache[pos - 1 + tileSize],
									cache[pos - 1]);	// tiling, skip count
						}
					}
					else
					{
						if (pos == 0)	// exception, -1
						{

							cache[pos - 1 + tileSize]
								= min(cache[pos - 1 + tileSize],
									tileSize);
						}
						else // match not found, prev + 1
						{
							cache[pos - 1 + tileSize]
								= min(cache[pos - 1 + tileSize],
									cache[pos - 1 + tileSize - 1] + 1);
						}
					}
				}
			}
		}
		return cache.back();
	}
	//
};
auto _ = []()
	{
		ios_base::sync_with_stdio(false);
		cin.tie(NULL), cout.tie(NULL);
		return 0;
	}();
	// solution class

	int main()
	{
		ios_base::sync_with_stdio(false);
		cin.tie(nullptr);
		cout.tie(nullptr);

		Solution test;
	}

