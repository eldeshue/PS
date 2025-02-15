
#include <iostream>
#include <vector>

using namespace std;

// solution
#include <array>
#include <bitset>

class Solution
{
private:
	array<int, 1024> cache;

public:
	// solution method
	long long wonderfulSubstrings(string word)
	{
		int result = 1;
		int status = 0;

		fill(cache.begin(), cache.end(), 0);
		for (int curIdx = 0; curIdx < word.size(); ++curIdx)
		{
			status ^= ;
			for ()
			{
				result += ;
			}
			cache[status]++;
		}
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
