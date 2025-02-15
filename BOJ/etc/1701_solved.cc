
#include <iostream>
#include <vector>
#include <string>

// failure function of kmp
// find prefix in itself.
int failureFunction(std::string_view target, std::vector<int> &table)
{
	int pos = 1, cnd = 0, result = 0;

	table[0] = -1;
	while (pos < target.size())
	{
		if (target[pos] == target[cnd])
		{
			table[pos] = table[cnd];
		}
		else	// mismatch
		{
			table[pos] = cnd;
			result = std::max(result, cnd);
			// find prefix in itself
			while (cnd >= 0 && target[cnd] != target[pos])
			{
				cnd = table[cnd];
			}
		}
		pos++;
		cnd++;
	}
	table[pos] = cnd;
	result = std::max(result, cnd);
	return result;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::string input;
	std::cin >> input;
	std::string_view target(input);
	std::vector<int> table(input.size() + 1, -1);
	int result = 0;
	for (int i = 0; i < input.size(); ++i)
	{
		result = std::max(result,
			failureFunction(target.substr(i, target.size() - i), table));
	}
	std::cout << result;
}
