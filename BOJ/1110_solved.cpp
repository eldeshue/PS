
#include <iostream>

int count_cycle(const int start)
{
	int cur_num = start;
	int cnt = 0;
	while (true)
	{
		int sum = cur_num / 10 + cur_num % 10;
		cur_num = sum % 10 + (cur_num % 10) * 10;
		cnt++;
		if (cur_num == start)
		{
			return cnt;
		}
	}
}

int main()
{
	int N;
	std::cin >> N;
	std::cout << count_cycle(N);
}
