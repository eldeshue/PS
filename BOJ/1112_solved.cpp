// BOJ, 1112
// 음의 진법 변환.
/*
	x = sigma ( a[n] ( b ) ^ n )

	x와 b가 주어지면 수열 a를 구해라.
		-> 밑(b)의 거듭제곱으로 나눈 나머지를 각 자리에 취하면 된다.

	*) b가 음수라면? -> 나머지 연산을 확장해야 할 필요가 있다.
		
		* 나머지 연산이란 무엇인가?
		a % b = a - (a * (a / b))
*/

#include <iostream>
#include <cmath>
#include <string>
	
int x, b;

void convert(std::string& result, int target, int radix)
{
	bool is_minus = false;

	if (target == 0)
	{
		result.push_back('0');
		return;
	}
	if (radix > 0 && target < 0)
	{
		target *= -1;
		is_minus = true;
	}
	while (target != 0)
	{
		int mod = target % radix;
		if (mod < 0)	// 음수에 대한 나머지 연산의 확장
		{
			result.push_back('0' + mod - radix);
			target /= radix;
			target++;
		}
		else
		{
			result.push_back('0' + mod);
			target /= radix;
		}
	}
	if (is_minus)
		result.push_back('-');
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::string result;
	std::cin >> x >> b;
	convert(result, x, b);
	for (auto ritr = result.rbegin(); ritr != result.rend(); ++ritr)
	{
		std::cout << *ritr;
	}
}
