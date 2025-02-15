
#include <iostream>
#include <memory.h>

int num_cmd;
int cups[4];

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(cups, 0, sizeof(cups));
	cups[1] = 1;

	int from, to;
	std::cin >> num_cmd;
	for (int i = 0; i < num_cmd; ++i)
	{
		std::cin >> from >> to;
		std::swap(cups[from], cups[to]);
	}
	int result = -1;
	for (int i = 1; i < 4; ++i)
	{
		if (cups[i] == 1)
			result = i;
	}
	std::cout << result;
}
