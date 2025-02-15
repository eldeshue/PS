
/*
	perfect square

	주어진 수 n을 제곱수square number로 분할하는데,
	분할 가능한 최소의 제곱수 개수를 구하기.

	1 <= n <= 10000 -> 1 ~ 100 사이의 수만 제곱으로 가능함.
*/
#include <iostream>

using namespace std;

// solution

class Solution
{
private:
	inline int square(int n) { return n * n; };
	bool splitSquare1(int n)
	{
		for (int i = 0; i < 100; ++i)
			if (square(i) == n)
				return true;
		return false;
	};
	bool splitSquare2(int n)
	{
		int fastPtr = 100, slowPtr = 0;
		while (square(fastPtr) > n && fastPtr > 0)
			fastPtr--;
		while (slowPtr <= fastPtr)
		{
			while (true)
			{
				int sum = square(fastPtr) + square(slowPtr);
				if (sum == n)
					return true;
				else if (sum > n)
					break;
				slowPtr++;
			}
			fastPtr--;
		}
		return (false);
	};
	bool splitSquare3(int n)
	{
		int k = 0;
		while (true)
		{
			int square_k = square(k);
			if (splitSquare2(n - square_k))
				return true;
			if (square_k > n)
				break;
			k++;
		}
		return false;
	};

public:
	// solution method
	int numSquares(int n)
	{
		if (splitSquare1(n))
			return 1;
		else if (splitSquare2(n))
			return 2;
		else if (splitSquare3(n))
			return 3;
		else
			return 4;
	}
};

//

// test
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;
	int input;
	std::cin >> input;
	std::cout << test.numSquares(input);
}
