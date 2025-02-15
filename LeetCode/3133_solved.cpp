
#include <iostream>

using namespace std;

// solution class

//#pragma GCC optimize("03")
//#pragma GCC target("avx")
//#pragma GCC target("-fsplit-loops")
#include <bitset>
class Solution
{
public:
	// solution method
	long long minEnd(int n, int x)
	{
		// x의 빈자리에 n-1의 비트를 순서대로 채워주면 됨.
		// 0번째는 x그 자체이므로 n-1임.
		bitset<64> N(n - 1);
		bitset<64> X(x);
		int xIdx = 0;
		for (int i = 0; i < 64; ++i)
		{
			while (X[xIdx])	// x의 빈자리로 포인터 이동
			{
				++xIdx;
			}
			X[xIdx] = N[i];
			++xIdx;
		}
		return X.to_ullong();
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
}

