
#include <iostream>
#include <string>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::string input, result;
	int N;
	std::cin >> N;
	std::cin >> result;
	for (int i = 0; i < N - 1; ++i)
	{
		std::cin >> input;
		int idx = 0;
		if (result.size() > input.size())
		{
			for (; idx < input.size(); ++idx)
			{
				if (result[idx] != input[idx])
				{
					result[idx] = '?';
				}
			}
			for (; idx < result.size(); ++idx)
			{
				result[idx] = '?';
			}
		}
		else
		{
			for (; idx < result.size(); ++idx)
			{
				if (result[idx] != input[idx])
				{
					result[idx] = '?';
				}
			}
			for (; idx < input.size(); ++idx)
			{
				result.push_back('?');
			}
		}
	}
	std::cout << result;
}