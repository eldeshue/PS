
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
	vector<int> vowelStrings(vector<string>& words, vector<vector<int>>& queries) {
		// query 내에서 vowel 문자열의 개수를 새는 것
		// vowel 문자열이라 함은 문자열의 시작과 끝 모두 모음으로 이루어진 문자열
		// 즉 query 범위 내에서 모음 순서 쌍의 개수를 구하는 문제임
		// 이는 prefix sum을 통해서 범위 내의 모음 개수를 구하여 해결할 수 있다.
		auto isVowel = [](char const c) {
			return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
			};
		auto isVowelStr = [isVowel](string const str) {
			return (isVowel(str.front()) && isVowel(str.back()));
			};

		// preprocessing
		const int N = words.size();
		vector<int> prefixVowelSum(N + 1, 0);
		for (int i = N - 1; i >= 0; --i)
		{
			prefixVowelSum[i] = prefixVowelSum[i + 1] + isVowelStr(words[i]);
		}

		// query handling
		vector<int> result;
		transform(queries.begin(), queries.end(), back_inserter(result), [&](vector<int> const& query) {
			int const left = query[0];
			int const right = query[1] + 1;
			return prefixVowelSum[left] - prefixVowelSum[right];
			});
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
