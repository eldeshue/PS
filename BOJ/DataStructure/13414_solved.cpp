/*
	BOJ 13414

	학번이 0으로 시작할 수 있어서 string으로...
*/
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int K, L;
	std::cin >> K >> L;
	std::unordered_map<std::string, int> last_stamp;
	for (int i = 0; i < L; ++i)
	{
		std::string id;
		std::cin >> id;
		last_stamp[id] = i;
	}
	std::vector<std::pair<int, std::string>> result;
	std::transform(last_stamp.begin(), last_stamp.end(), std::back_inserter(result),
		[](auto const& stat) {
			return std::make_pair(stat.second, stat.first);
		});
	std::sort(result.begin(), result.end());
	for (int i = 0; i < std::min(K, static_cast<int>(result.size())); ++i)
	{
		std::cout << result[i].second << '\n';
	}
}
