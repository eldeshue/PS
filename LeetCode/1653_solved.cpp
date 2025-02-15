
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
		// �����ʿ��� a�� ����ų� ���ʿ��� b�� �����
		// ������, ������ �����ϴ� ����� ����?
		// ������ ������ �Ǵ� ���� ��� �־� ������ �ذ��� �� ������?
		// ���� ���� �Űܰ��鼭 ������ ���� ã�´�.
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
		for (int i = 0; i < N; ++i)	// i�� �¿� ������ ���ؼ�
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

