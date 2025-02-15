// BOJ, 1112
// ���� ���� ��ȯ.
/*
	x = sigma ( a[n] ( b ) ^ n )

	x�� b�� �־����� ���� a�� ���ض�.
		-> ��(b)�� �ŵ��������� ���� �������� �� �ڸ��� ���ϸ� �ȴ�.

	*) b�� �������? -> ������ ������ Ȯ���ؾ� �� �ʿ䰡 �ִ�.
		
		* ������ �����̶� �����ΰ�?
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
		if (mod < 0)	// ������ ���� ������ ������ Ȯ��
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
