
#include <iostream>
#include <list>
#include <string>
#include <algorithm>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::string input;
	std::list<char> sentence;
	std::cin >> input;
	for (const char &c : input)
	{
		sentence.push_back(c);
	}
	auto cursor = sentence.end();
	int numQuery;
	std::cin >> numQuery;
	for (int i = 0; i < numQuery; ++i)
	{
		char cmd;
		std::cin >> cmd;
		if (cmd == 'L' && cursor != sentence.begin())
		{
			cursor--;
		}
		else if (cmd == 'D' && cursor != sentence.end())
		{
			cursor++;
		}
		else if (cmd == 'B' && cursor != sentence.begin())
		{
			auto target = --cursor;
			bool flag = (cursor == sentence.begin());
			if (!flag)
				cursor--;
			else
				cursor++;
			sentence.erase(target);
			if (!flag)
				cursor++;
		}
		else if (cmd == 'P')
		{
			char arg;
			std::cin >> arg;
			sentence.insert(cursor, arg);
		}
	}
	for (const char &c : sentence)
	{
		std::cout << c;
	}
}