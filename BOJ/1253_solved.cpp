
#include <iostream>
#include <set>

int N;
std::multiset<int> MS;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	
	int temp;
	std::cin >> N;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> temp;
		MS.insert(temp);
	}

	int result = 0;
	for (auto itr1 = MS.begin(); itr1 != MS.end(); ++itr1)	// O(N ^ 2)
	{
		for (auto itr2 = MS.begin(); itr2 != MS.end(); ++itr2)
		{
			int rest = *itr1 - *itr2;
			auto pos = MS.find(rest);
			if (pos == itr1)
			{
				if (*pos == 0)
				{
					pos++;
				}
			}
			if (pos != MS.end() && 
				pos != itr2 && pos != itr1  && itr1 != itr2
				)	// found,  exclude double check
			{
				result++;
				break;
			}
		}
	}
	std::cout << result;
}