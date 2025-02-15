
#include <iostream>
#include <vector>

using namespace std;

#pragma GCC optimize("03")
#pragma GCC target("avx")
#pragma GCC target("-fsplit-loops")
#include <algorithm>
class Solution
{
private:
public:
	// solution method
	int maximumSum(vector<int>& nums) {
		using pii = std::pair<int, int>;

		// transform
		vector<pii> buffer;
		transform(nums.begin(), nums.end(), back_inserter(buffer), [](int const n) {
			return make_pair([](int num) {
				int sum = 0;
				while (num)
				{
					sum += num % 10;
					num /= 10;
				}
				return sum;
				}(n), n);
			});

		// sort
		sort(buffer.begin(), buffer.end(), greater<pii>());

		// get max
		int result = -1;
		for (int i = 0; i < nums.size() - 1; ++i)
		{
			if (buffer[i].first == buffer[i + 1].first)
				result = max(result, buffer[i].second + buffer[i + 1].second);
		}
		return result;
	}
};
auto _ = []()
	{
		ios_base::sync_with_stdio(false);
		cin.tie(NULL), cout.tie(NULL);
		return 0;
	}();
//

// test
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;
}
