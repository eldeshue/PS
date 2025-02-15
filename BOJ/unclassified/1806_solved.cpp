
#include <iostream>
#include <cmath>

int N, S, minLength = 2e9;
int buffer[100000];

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> N >> S;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> buffer[i];
	}

	int start = 0, end = 0;
	int curVal = buffer[0];
	while(curVal > 0)
	{
		if (curVal >= S)
		{
			minLength = std::min(minLength, end - start + 1);
			if (start == end)
			{
				break;
			}
			else
			{
				curVal -= buffer[start++];
			}
		}
		else
		{
			if (end < N - 1)
			{
				curVal += buffer[++end];
			}
			else
			{
				break;
			}
		}
	}

	if (minLength == 2e9)
	{
		std::cout << 0;
	}
	else
	{
		std::cout << minLength;
	}
}