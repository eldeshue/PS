
#include <iostream>
#include <string>
#include <deque>

std::deque<int> DQ;

void do_command(const std::string& cmd)
{
	int val;
	if (cmd == "push_front")
	{
		std::cin >> val;
		DQ.push_front(val);
	}
	else if (cmd == "push_back")
	{
		std::cin >> val;
		DQ.push_back(val);
	}
	else if (cmd == "pop_front")
	{
		if (DQ.empty())
		{
			std::cout << -1 << '\n';
		}
		else
		{
			std::cout << DQ.front() << '\n';
			DQ.pop_front();
		}
	}
	else if (cmd == "pop_back")
	{
		if (DQ.empty())
		{
			std::cout << -1 << '\n';
		}
		else
		{
			std::cout << DQ.back() << '\n';
			DQ.pop_back();
		}
	}
	else if (cmd == "size")
	{
		std::cout << DQ.size() << '\n';
	}
	else if (cmd == "empty")
	{
		if (DQ.empty())
			std::cout << 1 << '\n';
		else
			std::cout << 0 << '\n';
	}
	else if (cmd == "front")
	{
		if (DQ.empty())
		{
			std::cout << -1 << '\n';
		}
		else
		{
			std::cout << DQ.front() << '\n';
		}
	}
	else if (cmd == "back")
	{
		if (DQ.empty())
		{
			std::cout << -1 << '\n';
		}
		else
		{
			std::cout << DQ.back() << '\n';
		}
	}
	else
	{
		;
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int num_command;
	std::string command;
	std::cin >> num_command;
	for (int i = 0; i < num_command; ++i)
	{
		std::cin >> command;
		do_command(command);
	}
}