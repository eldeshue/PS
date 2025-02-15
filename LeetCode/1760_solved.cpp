
#include <numeric>
class Solution {
public:
    int minimumSize(vector<int>& nums, int maxOperations) {
        int left = 1, right = 1e9 + 1;
        while (left < right)
        {
            const int mid = (left + right) >> 1;
            if (accumulate(nums.begin(), nums.end(), 0,
                [mid](const int acc, const int n) {
                    return acc + (n / mid) + ((n % mid) > 0) - 1;
                }) <= maxOperations)
                right = mid;
            else
                left = mid + 1;
        }
        return left;
    }
};