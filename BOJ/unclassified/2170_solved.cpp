
#include <iostream>
#include <algorithm>
#include <vector>

using line = std::pair<int, int>;
std::vector<line> input;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	std::cin >> N;
	for (int i = 0; i < N; ++i)
	{
		int f, t;
		std::cin >> f >> t;
		input.push_back(std::make_pair(f, t));
	}
	std::sort(input.begin(), input.end());

	// sweeping
	long long result = 0;
	int last_f = -2147483648, last_s = -2147483648;
	for (const line& cur_line : input)
	{
		if (cur_line.first <= last_s && last_s < cur_line.second)	// update
		{
			last_s = cur_line.second;
		}
		else if (last_s < cur_line.first) // add sum
		{
			result += last_s - last_f;
			last_f = cur_line.first;
			last_s = cur_line.second;
		}
	}
	result += last_s - last_f;
	std::cout << result;
}