
#include <iostream>
#include <memory.h>
#include <deque>

int numTest, numPaper, tgtPos;
std::deque<int> printer;
int numPriority[10]; // numPriority[ priority ] = number of paper with priority;

bool isTop(const int& p)
{
	for (int i = p + 1; i < 10; ++i)
	{
		if (numPriority[i] > 0)
		{
			return false;
		}
	}
	return true;
}

int print()
{
	int tgtCount = 0;

	while (!printer.empty())
	{
		if (isTop(printer.front())) // pop
		{
			tgtCount++;
			if (tgtPos == 0)
			{
				break;
			}
			else
			{
				numPriority[printer.front()]--;
				printer.pop_front();
				tgtPos--;
				numPaper--;
			}
		}
		else // revolve
		{
			printer.push_back(printer.front());
			printer.pop_front();
			if (tgtPos == 0)
			{
				tgtPos = numPaper - 1;
			}
			else
			{
				tgtPos--;
			}
		}
	}

	return tgtCount;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int temp;
	std::cin >> numTest;
	for (int i = 0; i < numTest; ++i)
	{
		printer.clear();
		memset(numPriority, 0, sizeof(numPriority));
		std::cin >> numPaper >> tgtPos;
		for (int j = 0; j < numPaper; ++j)
		{
			std::cin >> temp;
			numPriority[temp]++;
			printer.push_back(temp);
		}

		std::cout << print() <<"\n";
	}
}