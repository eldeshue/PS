
#include <iostream>
#include <string>
#include <deque>

int numCommand;
std::string command;
std::deque<int> Q;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int num;
	std::cin >> numCommand;
	for (int i = 0; i < numCommand; ++i)
	{
		std::cin >> command;
		if (command == "push")
		{
			std::cin >> num;
			Q.push_back(num);
		}
		else if (command == "pop")
		{
			if (Q.size() != 0)
			{
				std::cout << Q.front() << "\n";
				Q.pop_front();
			}
			else
			{
				std::cout << "-1\n";
			}
		}
		else if (command == "size")
		{
			std::cout << Q.size() << "\n";
		}
		else if (command == "empty")
		{
			if (Q.size() == 0)
			{
				std::cout << "1\n";
			}
			else
			{
				std::cout << "0\n";
			}
		}
		else if (command == "front")
		{
			if (Q.size() != 0)
			{
				std::cout << Q.front() << "\n";
			}
			else
			{
				std::cout << "-1\n";
			}
		}
		else if (command == "back")
		{
			if (Q.size() != 0)
			{
				std::cout << Q.back() << "\n";
			}
			else
			{
				std::cout << "-1\n";
			}
		}
		else
		{
			// error
			return 0;
		}
	}
}