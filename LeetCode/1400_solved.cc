
#include <iostream>
#include <vector>

using namespace std;

#pragma GCC optimize("03")
#pragma GCC target("avx")
#pragma GCC target("-fsplit-loops")
#include <array>
#include <numeric>
class Solution
{
private:
public:
	// solution method
	bool canConstruct(string s, int k) {
		// pelindrome split
		// 문자열 s의 문자를 적절하게 잘 사용하여 k개의 팰린드롬으로 분배하여야 한다.
		// 팰린드롬으로 분할 가능성 여부를 확인해야
		// 최대한 많이 만든다면 몇 개인가? s.size(), 즉 길이 1인 문자열은 팰린드롬임
		// 그렇다면, 최소로 가능한 팰린드롬 분할은 몇 개인가?
		// s가 lower case alphabet이므로, 홀 수개인 알파뱃의 종류의 수가 곧 답이다
		const int M = s.size();
		array<int, 26> freq{};

		for (const char c : s)
			++freq[c - 'a'];
		const int m = accumulate(freq.begin(), freq.end(), 0, [](const int acc, const int n) { return acc + (n & 1); });
		return ((m <= k) && (k <= M));
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
