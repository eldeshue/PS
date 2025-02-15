
// 임의의 변환을 n번 거친 후 얻은 문자열에서 k번째 위치한 값을 구한다.
// 해당 변환은 다음과 같다.
// 현재 문자열의 끝에 1을 붙이고
// 추가된 1을 기준으로 왼쪽을 대칭해서 붙인다.
// 대칭한 구역을 invert
// 반대로 생각해서 k번 위치에 있는 unknown value를 역추적 하면 되는것 아닌가?

#include <iostream>

using namespace std;

// solution class

//#pragma GCC optimize("03")
//#pragma GCC target("avx")
//#pragma GCC target("-fsplit-loops")

class Solution
{
public:
	// solution method
	char findKthBit(int n, int k)
	{
		bool inverse = false;
		bool start = false;
		int len = 1;
		for (int i = 0; i < n - 1; ++i)
			len = 2 * len + 1;
		// calculate length of n'th 
		for (int i = 0; i < n - 1; ++i)
		{
			// reverse transform
			const int mid = len / 2 + 1;
			if (len == 1)
			{
				start = false;
				break;
			}
			else if (len != 1 && k == mid) // mid, break
			{
				start = true;
				break;
			}
			else if (k > mid) // right, reverse and inverse k
			{
				inverse = !inverse;
				k = len - k + 1;
			}
			else
			{
				// left, do nothing
			}
			len /= 2;
		}
		if (inverse)
			start = !start;
		return '0' + start;
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

