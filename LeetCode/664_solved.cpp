
/*

#include <iostream>
#include <vector>

using namespace std;

// solution class

//#pragma GCC optimize("03")
//#pragma GCC target("avx")
//#pragma GCC target("-fsplit-loops")

class Solution
{
private:
    int minimumTurns(int start, int end, string& s, vector<vector<int>>& memo)
    {
        if (start > end) // Base case: empty string requires 0 turns
        {
            return 0;
        }
        else if (memo[start][end] != -1)    // cache hit
        {
            return memo[start][end];
        }
        else // cache miss
        {
            // Initialize with worst case: print each character separately
            int minTurns = 1 + minimumTurns(start + 1, end, s, memo);

            // Try to optimize by finding matching characters
            for (int k = start + 1; k <= end; k++)
            {
                if (s[k] == s[start])   // both end matched
                {
                    // If match found, try splitting the problem
                    // skip the count of s[k]
                    // because it is already counted at the beginning, s[start]
                    int turnsWithMatch = minimumTurns(start, k - 1, s, memo) +
                        minimumTurns(k + 1, end, s, memo);
                    minTurns = min(minTurns, turnsWithMatch);
                }
            }

            // Memoize and return the result
            return memo[start][end] = minTurns;
        }
    }

    string removeDuplicates(string& s)
    {
        string uniqueChars;
        int i = 0;
        while (i < s.length())
        {
            const char &currentChar = s[i];
            uniqueChars.push_back(currentChar);
            // Skip all consecutive occurrences of the current character
            while (i < s.length() && s[i] == currentChar)
                i++;
        }
        return uniqueChars;
    }

public:
    int strangePrinter(string s)
    {
        // Preprocess the string to remove consecutive duplicate characters
        s = removeDuplicates(s);
        const int n = s.length();
        // Initialize memoization array
        vector<vector<int>> cache(n, vector<int>(n, -1));
        // Start the recursive process
        return minimumTurns(0, n - 1, s, cache);
    }
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

    */
