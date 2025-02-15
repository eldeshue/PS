
#include <array>
#include <algorithm>
#include <numeric>
class Solution {
public:
    int largestCombination(vector<int>& candidates)
    {
        array<int, 32> freq;
        fill(freq.begin(), freq.end(), 0);
        for_each(candidates.begin(), candidates.end(), [&](const int n) {
            for (int i = 0; i < 32; ++i)
            {
                freq[i] += ((n & (1 << i)) > 0);
            }
            });
        return accumulate(freq.begin(), freq.end(), 0, [](const int a, const int b) {
            return max(a, b);
            });
    }
};