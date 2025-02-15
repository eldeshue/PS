
#include <iostream>
#include <vector>

using namespace std;

//#pragma GCC optimize("03")
//#pragma GCC target("avx")
//#pragma GCC target("-fsplit-loops")
#include <unordered_set>
#include <bit>
class Solution
{
private:
	struct CustomHash
	{
		size_t operator()(pair<char, char> const& p) const
		{
			return (hash<char>()(p.first) | rotl(hash<char>()(p.second), 2));
		}
	};
public:
	// solution method
	int countPalindromicSubsequence(string s)
	{
		const int N = s.size();
		vector<vector<int>> prefixSum(N, vector<int>(26, 0));

		prefixSum[0][s[0] - 'a']++;
		for (int i = 1; i < N; ++i)
		{
			prefixSum[i] = prefixSum[i - 1];
			prefixSum[i][s[i] - 'a']++;
		}

		unordered_set<pair<char, char>, CustomHash> result;
		for (int mid = 1; mid < N - 1; ++mid)
		{
			for (char i = 0; i < 26; ++i)
			{
				if (prefixSum[mid - 1][i]
					&& prefixSum[N - 1][i] - prefixSum[mid][i])
					result.insert(make_pair(s[mid], 'a' + i));
			}
		}
		return result.size();
	}
	//
};
auto _ = []()
	{
		ios_base::sync_with_stdio(false);
		cin.tie(NULL), cout.tie(NULL);
		return 0;
	}();

	int main()
	{
		ios_base::sync_with_stdio(false);
		cin.tie(nullptr);
		cout.tie(nullptr);

		Solution test;
	}


