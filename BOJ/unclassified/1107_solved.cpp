
#include <iostream>
#include <string>
#include <set>

std::set<char> isBroken;
bool isChannel[1000001];

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	char temp;
	int goal, M;
	std::cin >> goal >> M;
	for (int i = 0; i < M; ++i)
	{
		std::cin >> temp;
		isBroken.insert(temp);
	}

	for (int i = 0; i < 1000001; ++i)
	{
		std::string numStr = std::to_string(i);
		isChannel[i] = true;
		for (const auto& elem : numStr)
		{
			if (isBroken.find(elem) != isBroken.end())
			{
				isChannel[i] = false;
				break;
			}
		}
	}

	int nearest = 100;
	int big = goal, small = goal;
	while (small != 0 || big != 1000000)
	{
		if (isChannel[small])
		{
			nearest = small;
			break;
		}
		else if (isChannel[big])
		{
			nearest = big;
			break;

		}
		else
		{
			if (big < 1000000)
			{
				big++;
			}
			if (small > 0)
			{
				small--;
			}
		}
	}
	int result1 = std::abs(goal - 100);
	int result2 = std::to_string(nearest).size() + std::abs(nearest - goal);
	if (result1 < result2)
	{
		std::cout << result1;
	}
	else
	{
		std::cout << result2;
	}
}