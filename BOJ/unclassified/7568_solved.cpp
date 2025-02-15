
#include <iostream>
#include <vector>

using P = std::pair<int, int>;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	std::cin >> N;
	std::vector<P> people(N);
	std::vector<int> result(N, 0);
	for (int i = 0; i < N; ++i)
		std::cin >> people[i].first >> people[i].second;
	for (int i = 0; i < N; ++i)
	{
		const P& me = people[i];
		for (int j = 0; j < N; ++j)
		{
			const P& you = people[j];
			if (me.first < you.first && me.second < you.second )
			{
				result[i]++;
			}
		}
		result[i]++;
	}
	for (const int& r : result)
	{
		std::cout << r << ' ';
	}
}