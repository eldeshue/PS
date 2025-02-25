#include <vector>

using namespace std;

class Solution {
public:
    int numOfSubarrays(vector<int>& arr) {
        // suffix array
        using pii = pair<int, int>;
        int const N = arr.size();
        int const DIV = 1e9 + 7;

        int sum = arr[0] & 1;
        int result = sum;
        vector<pii> suffix_arr(N, {0, 0});
        suffix_arr[0] = std::make_pair((arr[0] & 1) , !(arr[0] & 1));
        for (int i = 1; i < N; ++i)
        {
            // update current sum
            sum += arr[i];
            sum &= 1;
            result += sum;

            // count sub arr from prev suffix array
            if (sum)
            {
                // current odd, get prev event
                result += suffix_arr[i - 1].second;
            }
            else
            {
                // opposite
                result += suffix_arr[i - 1].first;
            }

            // update suffix array
            suffix_arr[i] = suffix_arr[i - 1];
            suffix_arr[i].first += sum;
            suffix_arr[i].second += !sum;

            // divide
            result %= DIV;
        }
        return result;
    }
};
