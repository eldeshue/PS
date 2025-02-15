
#include <iostream>
#include <vector>
#include <string>

bool test_pellindrom(const std::string& str)
{
	int size = str.size();
	int test_range = size / 2;
	for (int i = 0; i < test_range; ++i)
	{
		if (str[i] != str[size - 1 - i])
		{
			return false;
		}
	}
	return true;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::vector<bool> result;
	std::string temp;
	while (true)
	{
		std::cin >> temp;
		if (temp.front() == '0')
		{
			break;
		}
		result.push_back(test_pellindrom(temp));
	}

	for (const auto& elem : result)
	{
		std::cout << (elem ? "yes\n" : "no\n");
	}
}
