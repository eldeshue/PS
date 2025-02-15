
#include<iostream>
#include <string>

int numTest, val, SP = -1;
int stack[10000];
std::string cmd;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> numTest;
	for (int i = 0; i < numTest; ++i)
	{
		std::cin >> cmd;
		if (cmd == "push")
		{
			std::cin >> val;
			stack[++SP] = val;
		}
		else if (cmd == "pop")
		{
			if (SP == -1)
			{
				std::cout << -1 << "\n";
			}
			else
			{
				std::cout << stack[SP--] << "\n";
			}
		}
		else if (cmd == "size")
		{
			std::cout << SP + 1 << "\n";
		}
		else if (cmd == "empty")
		{
			if (SP == -1)
			{
				std::cout << "1\n";
			}
			else
			{
				std::cout << "0\n";
			}
		}
		else if (cmd == "top")
		{
			if (SP == -1)
			{
				std::cout << -1 << "\n";
			}
			else
			{
				std::cout << stack[SP] << "\n";
			}
		}
		else
		{
			abort();
		}
	}
}
