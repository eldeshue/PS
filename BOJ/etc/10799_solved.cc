
#include <iostream>
#include <string>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	bool isPrevClose = false;
	int cnt = 0, result = 0;
	std::string str;
	std::cin >> str;
	for (const char &c : str)
	{
		if (c == ')')
		{
			cnt--;
			if (isPrevClose)
				result++;
			else
				result += cnt;
			isPrevClose = true;
		}
		else // c == '('
		{
			cnt++;
			isPrevClose = false;
		}
	}
	std::cout << result;
}
