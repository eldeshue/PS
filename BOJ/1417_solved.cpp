
#include <iostream>
#include <algorithm>
#include <vector>

bool compare(int a, int b)
{
	return a > b;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, input;
	std::cin >> N;
	std::vector<int> vec;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> input;
		vec.push_back(input);
	}
	std::sort(vec.begin() + 1, vec.end(), compare);
	int prev = vec.front();
	for (int i = 1; i < N; ++i)
	{
		while (vec.front() <= vec[i])
		{
			vec.front()++;
			vec[i]--;
			std::sort(vec.begin() + i, vec.end(), compare);
		}
	}
	std::cout << vec.front() - prev;
}