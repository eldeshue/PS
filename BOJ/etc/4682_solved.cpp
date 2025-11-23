/*
	BOJ 4682

	다항식의 계수를 받아서 일반적인(사람이 주로 사용하는) 방법으로 표현하기

	생각보다 까다로운 경우의 수가 좀 있어서, 괴로운 문제였다.
*/

#include <iostream>
#include <vector>
#include <array>
#include <string>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::array<int, 9> exp = {};
	while (std::cin >> exp[0])
	{
		// input
		bool is_all_zero = true;
		for (int i = 1; i < 9; ++i)
		{
			std::cin >> exp[i];
			is_all_zero &= (exp[i] == 0);
		}

		if (is_all_zero)
		{
			std::cout << "0\n";
			continue;
		}

		std::string str;
		for (int i = 0; i < 9; ++i)
		{
			// coefficient
			if (exp[i] == 0 && i != 8)
			{
				continue;
			}
			else
			{
				// sign
				if (!str.empty() && exp[i] > 0)
				{
					str += "+ ";
				}
				else if (exp[i] < 0)
				{
					if (str.empty())
						str.push_back('-');
					else
						str += "- ";
				}

				// number
				if (std::abs(exp[i]) != 1 || i == 8)
				{
					if (i != 8 || exp[i] != 0)
						str += std::to_string(std::abs(exp[i]));
				}
			}

			// 
			int pow = 8 - i;
			if (pow == 0)
			{
				continue;
			}
			else
			{
				str.push_back('x');
				if (pow != 1)
				{
					str.push_back('^');
					str += std::to_string(pow);
				}
				str.push_back(' ');
			}
		}
		std::cout << str << std::endl;
	}
}
