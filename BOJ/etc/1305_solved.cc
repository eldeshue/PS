
#include <iostream>
#include <string>
#include <vector>

int failureFunction(std::string_view sv)
{
	std::vector<int> jmpTable(sv.size() + 1, -1);

	int pos = 1, cnd = 0;
	while (pos < sv.size())
	{
		// match
		if (sv[pos] == sv[cnd])
		{
			jmpTable[pos] = jmpTable[cnd];
		}
		else
		{
			// mismatch, find last candidate
			jmpTable[pos] = cnd;
			while (cnd >= 0 && sv[pos] != sv[cnd])
			{
				cnd = jmpTable[cnd];
			}
		}
		pos++;
		cnd++;
	}
	return cnd;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int winSize;
	std::string window;
	std::cin >> winSize >> window;
	std::cout << winSize - failureFunction(window);
}
