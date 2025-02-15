
/*
#include <iostream>
#include <vector>
#include <memory.h>

bool ab_table[201][201];

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(ab_table, 0, sizeof(ab_table));

	int N, input;
	std::vector<int> vec;
	std::cin >> N;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> input;
		vec.push_back(input);
	}
	// init set
	int a, b;
	int table_size = 0;
	int max_a = vec[1] / vec[0];
	for (a = 0; a <= max_a; ++a)
	{
		b = vec[1] - vec[0] * a;
		ab_table[a + 100][b + 100] = true;
		table_size++;
	}
	// search, N ^ 2
	for (int i = 2; i < N; ++i)
	{
		max_a = vec[i] / vec[i - 1];
		for (a = 0; i <= max_a; ++a)
		{
			b = vec[i] - vec[i - 1] * a;
			if (ab_table[a + 100][b + 100] == true)
			{
				ab_table[a + 100][b + 100] = false;
				table_size--;
			}
		}
	}
	// result
	if (table_size > 1)
	{
		std::cout << 'A';
	}
	else if (table_size == 0)
	{
		std::cout << 'B';
	}
	else
	{
		for (int i = 0; i < 201; ++i)
		{
			for (int j = 0; j < 201; ++j)
			{
				if (ab_table[i][j] == true)
				{
					a = i - 100;
					b = j - 100;
					break;
				}
			}
		}
		std::cout << a * vec[N - 1] + b;
	}
}

*/