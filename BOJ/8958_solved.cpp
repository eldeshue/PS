
#include <iostream>
#include <string>

std::string input_str;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int test_num;
	std::cin >> test_num;
	for (int i = 0; i < test_num; ++i)
	{
		int cur_point = 0;
		int total_point = 0;
		std::cin >> input_str;
		for (const auto c : input_str)
		{
			if (c == 'O')
				cur_point++;
			else
				cur_point = 0;
			total_point += cur_point;
		}
		std::cout << total_point << "\n";
	}
}