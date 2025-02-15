
#include <iostream>
#include <string>

int goal, nearest;
bool isBroke[10];

int int_length(int n)
{
	int length = 0;
	do
	{
		n /= 10;
		length++;
	} while (n != 0);
	return length;
}



void calcNearest(int num)
{
	int smallestAmongBig = goal, biggestAmongSmall = goal;
	std::string numStr = std::to_string(num);
	
	// find anavailable position
	int pos, pivot;
	for (pos = numStr.size() - 1; pos >= 0; --pos)
	{
		if (isBroke[numStr[pos] - '0'])
		{
			pivot = numStr[pos] - '0';
			break;
		}
	}
	if (pos == 0)
	{
		nearest = num;
		return;
	}
	///////////////////////////////////////////
	int nearSmall, nearBig, biggest, smallest;
	for (int i = pivot - 1; i >= 0; --i)
	{
		if (!isBroke[i])
		{
			nearSmall = i;
			break;
		}
	}
	for (int i = pivot + 1; i < 10; ++i)
	{
		if (!isBroke[i])
		{
			nearBig = i;
			break;
		}
	}
	for (int i = 9; i >= 0; --i)
	{
		if (!isBroke[i])
		{
			biggest = i;
			break;
		}
	}
	for (int i = 0; i < 10; ++i)
	{
		if (!isBroke[i])
		{
			smallest = i;
			break;
		}
	}
	////////////////////////////////////////
	for (int i = 0; i < pos; ++i)
	{
		numStr[i] = biggest + '0';
	}
	numStr[pos] = nearSmall + '0';
	biggestAmongSmall = std::stoi(numStr);
	
	for (int i = 0; i < pos; ++i)
	{
		numStr[i] = smallest + '0';
	}
	numStr[pos] = nearBig + '0';
	smallestAmongBig = std::stoi(numStr);


	if (std::abs(goal - smallestAmongBig) < std::abs(goal - biggestAmongSmall))
	{
		nearest = smallestAmongBig;
	}
	else
	{
		nearest = biggestAmongSmall;
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	for (int i = 0; i < 10; ++i)
	{
		isBroke[i] = false;
	}

	int numFail, temp;
	std::cin >> goal >> numFail;
	if (goal == 100)
	{
		std::cout << 0;
		return 0;
	}
	for (int i = 0; i < numFail; ++i)
	{
		std::cin >> temp;
		isBroke[temp] = true;
	}

	calcNearest(goal);
	int result1 = std::abs(goal - 100);;
	int result2 = int_length(nearest) + std::abs(goal - nearest);
	if ( result1 > result2 )
	{
		std::cout << result2;
	}
	else
	{
		std::cout << result1;
	}
}