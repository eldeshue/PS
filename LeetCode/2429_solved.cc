
#include <iostream>
#include <vector>

using namespace std;

//#pragma GCC optimize("03")
//#pragma GCC target("avx")
//#pragma GCC target("-fsplit-loops")
#include <bitset>
class Solution
{
private:
public:
	// solution method : greedy + bitset
	int minimizeXor(int num1, int num2)
	{
		// count number of bit from num2
		int numBit = bitset<32>(num2).count();
		// to minimize xor, we should keep x and num1 same as possible
		// copy num1 form msb about number of bit from num2
		int x = 0;
		for (int i = 31; i >= 0; --i)
		{
			if (numBit && (num1 & (1 << i)))	// as same as num1, set bit to x
			{
				x |= (1 << i);
				--numBit;
			}
		}
		// handling left over numBit
		// set bit from lsb to minimize x xor num1
		int i = 0;
		while (numBit)
		{
			if (!(x & (1 << i)))
			{
				--numBit;
				x |= (1 << i);
			}
			i++;
		}
		return x;
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
	std::cout << test.minimizeXor(3, 5) << ' ' << test.minimizeXor(1, 12);
}
