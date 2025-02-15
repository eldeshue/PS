
// ������ ��ȯ�� n�� ��ģ �� ���� ���ڿ����� k��° ��ġ�� ���� ���Ѵ�.
// �ش� ��ȯ�� ������ ����.
// ���� ���ڿ��� ���� 1�� ���̰�
// �߰��� 1�� �������� ������ ��Ī�ؼ� ���δ�.
// ��Ī�� ������ invert
// �ݴ�� �����ؼ� k�� ��ġ�� �ִ� unknown value�� ������ �ϸ� �Ǵ°� �ƴѰ�?

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

