
#include <iostream>

int num_card;
int goal;
int cards[100];

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> num_card >> goal;
	for (int i = 0; i < num_card; ++i)
	{
		std::cin >> cards[i];
	}

	int result = 0;
	for (int i = 0; i < num_card - 2; ++i)
	{
		for (int j = i + 1; j < num_card - 1; ++j)
		{
			for (int k = j + 1; k < num_card; ++k)
			{
				int temp = cards[i] + cards[j] + cards[k];
				if ((goal - temp) >= 0 && temp > result)
				{
					result = temp;
				}
			}
		}
	}
	std::cout << result << "\n";
}