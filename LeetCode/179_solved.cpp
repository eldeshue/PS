
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// solution class

//#pragma GCC optimize("03")
//#pragma GCC target("avx")
//#pragma GCC target("-fsplit-loops")
#include <algorithm>
#include <numeric>
class Solution {
public:
    // functional programming
    string largestNumber(vector<int>& nums) {
        vector<string> numStr;
        if (all_of(nums.begin(), nums.end(), [](const int n) {return n == 0; }))
            return "0";
        transform(nums.begin(), nums.end(), back_inserter(numStr), [](const int n) {return to_string(n); });
        sort(numStr.begin(), numStr.end(), [](const string& str1, const string& str2) {
            int idx1 = 0, idx2 = 0;
            while (true)
            {
                if (str1[idx1] != str2[idx2])
                    return str1[idx1] > str2[idx2];
                idx1++; idx2++;
                if (idx1 == str1.size() && idx2 == str2.size())
                    break;
                if (idx1 == str1.size())
                    idx1 = 0;
                if (idx2 == str2.size())
                    idx2 = 0;
            }
            return true;
            });
        return accumulate(numStr.begin(), numStr.end(), string(""));
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

