
#include <iostream>

using namespace std;

// solution class
#include <vector>
constexpr int MOD = 1000000007;

class Solution {
    vector<vector<vector<int>>> cache;

private:
    int dp(int n, int cntA, int consecL)    // memoize
    {
        if (cntA >= 2 or consecL >= 3) // fail
        {
            return 0;
        }
        else if (cache[n][cntA][consecL] != -1) // cache hit
        {
            return cache[n][cntA][consecL];
        }
        else if (n == 0)    // base case
        {
            return cache[n][cntA][consecL] = 1;
        }
        else   // cache miss
        {
            // We choose 'P' for the current position.
            int count = dp(n - 1, cntA, 0);
            // We choose 'A' for the current position.
            count = (count + dp(n - 1, cntA + 1, 0)) % MOD;
            // We choose 'L' for the current position.
            count = (count + dp(n - 1, cntA, consecL + 1)) % MOD;

            // Return and store the current sub-problem result in the cache.
            return cache[n][cntA][consecL] = count;
        }
    }
public:
    int checkRecord(int n)
    {
        // Initialize the cache.
        cache = vector<vector<vector<int>>>(n + 1, vector<vector<int>>(2, vector<int>(3, -1)));
        return dp(n, 0, 0);
    }
};

// solution class

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;

}