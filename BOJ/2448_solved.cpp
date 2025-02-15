
#include <iostream>
#include <memory.h>

int N;
bool buffer[3073][6145];

void setBaseTri(int offsetX, int offsetY)
{
	buffer[offsetY][offsetX] = true;
	buffer[offsetY + 1][offsetX - 1] = true;
	buffer[offsetY + 1][offsetX + 1] = true;
	for (int i = -2; i < 3; ++i)
		buffer[offsetY + 2][offsetX + i] = true;
}

void setBuffer(int posX, int posY, int length)
{
	if (length == 3)
	{
		setBaseTri(posX, posY);
		return;
	}

	int nextLength = length / 2;
	setBuffer(posX, posY, nextLength );	// ²ÀÁþÁ¡
	setBuffer(posX - nextLength , posY + nextLength , nextLength );	// left tree
	setBuffer(posX + nextLength , posY + nextLength , nextLength );	// right tree
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(buffer, 0, sizeof(buffer));

	std::cin >> N;
	setBuffer(N, 1, N);

	for (int y = 1; y <= N; ++y)
	{
		for (int x = 1; x <= 2 * N - 1; ++x)
		{
			if (buffer[y][x])
			{
				std::cout << "*";
			}
			else
			{
				std::cout << " ";
			}
		}
		std::cout << "\n";
	}
}