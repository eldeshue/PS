
/*
#include <iostream>

using namespace std;

// solution class

//#pragma GCC optimize("03")
//#pragma GCC target("avx")
//#pragma GCC target("-fsplit-loops")

// prefix tree
class Solution {
private:
    int countSteps(int n, long prefix1, long prefix2) // calculate numbers between prefix1 and prefix2
    {
        int steps = 0;
        while (prefix1 <= n) {
            steps += min((long)(n + 1), prefix2) - prefix1; // accumulate
            prefix1 *= 10;  // go deeper
            prefix2 *= 10;
        }
        return steps;
    }
public:
    int findKthNumber(int n, int k) {
        int curr = 1;   // current number, 1 is smallest
        k--;            // count 1

        while (k > 0)   // until we count all the number smaller than k
        {
            int step = countSteps(n, curr, curr + 1);
            if (k >= step)
            {
                curr++; // move to adjacent subtree, brother?
                k -= step;
            }
            else    // bigger than k, k th number is in the subtree, go deeper
            {
                curr *= 10;
                k--;    // count prefix itself
            }
        }

        return curr;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Solution test;
}
*/
