// greedy, failed
#include <iostream>

int curL = 0, curR = 0, curCost = 0;

void minMov(int nextNum)
{
	if (curL == nextNum || curR == nextNum)
	{
		curCost++;
	}
	else if (curL == 0)
	{
		curL = nextNum;
		curCost += 2;
	}
	else if (curR == 0)
	{
		curR = nextNum;
		curCost += 2;
	}
	else if (std::abs(nextNum - curL) % 2 == 1)
	{
		curL = nextNum;
		curCost += 3;
	}
	else if (std::abs(nextNum - curR) % 2 == 1)
	{
		curR = nextNum;
		curCost += 3;
	}
	else if (std::abs(nextNum - curL) % 2 == 0)
	{
		curL = nextNum;
		curCost += 4;
	}
	else
	{
		curR = nextNum;
		curCost += 4;
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	char input;
	std::cin >> input;
	while(input != '0')
	{ 
		minMov(input - '0');
		std::cout << curL << " " << curR << " " << curCost << "\n";
		std::cin >> input;
	}
	std::cout << curCost;
}