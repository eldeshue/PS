
#include <iostream>
#include <string>
#include <set>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	char query;
	int testNum, opsNum, target;
	std::cin >> testNum;
	for (int i = 0; i < testNum; ++i)
	{
		std::multiset<int> dePQ;
		std::cin >> opsNum;
		for (int j = 0; j < opsNum; ++j)
		{
			std::cin >> query >> target;
			if (query == 'I')
				dePQ.insert(target);
			else
			{
				if (dePQ.empty())
					continue;
				if (target == 1)
					dePQ.erase(--dePQ.end());
				else // target == -1
					dePQ.erase(dePQ.begin());
			}
		}
		if (dePQ.empty())
			std::cout << "EMPTY\n";
		else
			std::cout << *dePQ.rbegin() << ' ' << *dePQ.begin() << '\n';
	}
}