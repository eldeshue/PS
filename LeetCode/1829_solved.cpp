
using namespace std;

#include <vector>
#include <numeric>
#include <algorithm>
class Solution {
public:
    vector<int> getMaximumXor(vector<int>& nums, int maximumBit) {
        const int n = nums.size();
        const int mask = (1 << maximumBit) - 1;
        vector<int> result(n);
        int xorSum = accumulate(nums.begin(), nums.end(), 0,
            [](const int a, const int b) { return a ^ b; });
        transform(nums.rbegin(), nums.rend(), result.begin(),
            [&](const int num) {
                const int k = mask & (~xorSum);
                xorSum ^= num;
                return k;
            });
        return result;
    }
};