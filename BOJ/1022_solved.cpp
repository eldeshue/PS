
#include <iostream>

int minX, minY, maxX, maxY, maxNum = 0;
int buffer[50][5];

int getSpace(int val)
{
	int cnt = 0;
	while (std::abs(val) > 0)
	{
		val /= 10;
		cnt++;
	}
	return cnt;
}

void putVal(int x, int y)
{
	// find seg
	int val;
	if (x == 0 && y == 0)
	{
		val = 1;
	}
	else if (x > 0 && x > y && y >= -x)
	{
		int offset = x + y;
		val = 4 * x * x - 2 * x + 1 - offset;
	}
	else if (y < 0 && -y > x && x >= y)
	{
		int offset = -y + x;
		val = 4 * y * y + 1 - offset ;
	}
	else if (x < 0 && y > x && y <= -x)
	{
		int offset = -x - y;
		val = 4 * x * x - 2 * x + 1 - offset ;
	}
	else // y > 0 && x > -y
	{
		int offset = y - x;
		val = 4 * y * y + 4 * y + 1 - offset ;
	}
	buffer[y - minY][x - minX] = val;
	maxNum = std::max(maxNum, val);
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> minY >> minX >> maxY >> maxX;
	
	for (int i = minY; i <= maxY; ++i)
	{
		for (int j = minX; j <= maxX; ++j)
		{
			putVal(j, i);
		}
	}
	// set space
	int space = getSpace(maxNum);
	//
	for (int i = 0; i <= maxY - minY; ++i)
	{
		for (int j = 0; j <= maxX - minX; ++j)
		{
			std::cout.width(space);
			std::cout << buffer[i][j] << " ";
		}
		std::cout << "\n";
	}
}