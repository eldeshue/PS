
#include <iostream>
#include <string>

std::string buffer;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	char c;
	int tempVal = 0, totalVal = 0, level = 1;
	std::cin >> buffer;
	int pos = buffer.size() - 1;
	while (pos >= 0)
	{
		c = buffer[pos];
		if (c == '-')
		{
			totalVal -= tempVal;
			tempVal = 0;
			level = 1;
		}
		else if (c == '+')
		{
			level = 1;
		}
		else
		{
			c -= '0';
			tempVal += c * level;
			level *= 10;
		}
		pos--;
	}

	totalVal += tempVal;
	std::cout << totalVal;
}