
#include <iostream>
#include <string>
#include <unordered_set>

bool isGroupWord(const std::string &str)
{
	std::unordered_set<char> table;
	char prevC = str[0];
	table.insert(prevC);
	for (const char &c : str)
	{
		if (prevC != c)
		{
			if (table.find(c) != table.end())
				return false;
			table.insert(c);
			prevC = c;
		}
	}
	return true;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::string str;
	int N, result = 0;
	std::cin >> N;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> str;
		result += isGroupWord(str);
	}
	std::cout << result;
}
