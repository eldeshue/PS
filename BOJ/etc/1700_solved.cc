
/*
	그리디 알고리즘. -> 가장 나중에 만나는 녀석을 교체해야 이득이다.

	운영체제론, page swap algorithm, OPT 알고리즘.
*/
#include <iostream>
#include <vector>
#include <unordered_set>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::unordered_set<int> curItem; // on memory process
	int N, K;
	std::cin >> N >> K;
	std::vector<int> items(K); // scheduled
	for (int i = 0; i < K; ++i)
		std::cin >> items[i];
	// traverse
	int swapCount = 0;
	for (int i = 0; i < K; ++i)
	{
		if (curItem.find(items[i]) == curItem.end())
		{
			if (curItem.size() == N)
			{
				// pick victim, last appear in the future
				int victim = -1;
				int latestAppear = -1;
				for (const int &ci : curItem)
				{
					int nextAppear = [&]() -> int
					{
						for (int pos = i; pos < K; ++pos)
						{
							if (ci == items[pos])
								return pos;
						}
						return K;
					}();
					if (nextAppear > latestAppear)
					{
						victim = ci;
						latestAppear = nextAppear;
					}
				}
				// swap
				curItem.erase(victim);
				swapCount++;
			}
			curItem.insert(items[i]);
		}
	}
	std::cout << swapCount;
}
