#include <unordered_set>
class Solution {
public:
    string findDifferentBinaryString(vector<string>& nums) {
        int const N = nums.size();
        auto strToInt = [](string const &str){
            int result = 0;
            for (int i = 0; i < str.size(); ++i)
            {
                result |= (str[i] == '1') << i;
            }
            return result;
        };
        auto intToStr = [=](int const n){
            string result(N, '0');
            for (int i = 0; i < N; ++i)
            {
                result[i] += !!(n & (1 << i));
            }
            return result;
        };

       unordered_set<int> already_appeared;
       for (auto const &str : nums)
       {
        already_appeared.insert(strToInt(str));
       }

        for (int i = 0; i < 2e9; ++i)
        {
            if (already_appeared.find(i) == already_appeared.end())
            {
                return intToStr(i);
            }
        }
        return "";
    }
};
