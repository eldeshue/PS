
#include <iostream>
#include <string>

using namespace std;

// solution class

//#pragma GCC optimize("03") // compiler optimization
//#pragma GCC target("avx")  // SIMD
//#pragma GCC target("-fsplit-loops")  // loop unroll
class Solution
{
public:
	// solution method
	int minimumDeletions(string s)
	{
		// 오른쪽에서 a를 지우거나 왼쪽에서 b를 지운다
		// 오른쪽, 왼쪽을 구분하는 방법이 뭐지?
		// 구분의 기준이 되는 선을 어디에 둬야 문제를 해결할 수 있을까?
		// 기준 선을 옮겨가면서 최적의 답을 찾는다.
		// meet in the middle? prefix and suffix sum?
		const int N = s.size();
		int totalA = 0, prefixA = 0, prefixB = 0;

		// init prefix
		for (int i = 0; i < N; ++i)
		{
			if (s[i] == 'a')
				totalA++;
		}
		int result = std::min(totalA, N - totalA); // only one kind of character
		for (int i = 0; i < N; ++i)	// i가 좌우 분할의 기준선
		{
			if (s[i] == 'a')
				prefixA++;
			else
				prefixB++;
			// find minimum
			// erase character num = prefixB + suffixA
			// totalA - prefixA = suffix A
			result = std::min(result, prefixB + totalA - prefixA);
		}
		return result;
	}
	//
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
	std::cout << test.minimumDeletions("bbbb") << '\n';
	std::cout << test.minimumDeletions("a") << '\n';
	std::cout << test.minimumDeletions("ababaaaabbbbbbbb") << '\n';	// erase 2 'b'
}

