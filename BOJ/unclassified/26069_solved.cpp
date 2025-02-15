
#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::unordered_map<std::string, bool> isDancing;
	isDancing.insert({ "ChongChong", true });
	int N;
	std::cin >> N;
	while (N--)
	{
		std::string a, b;
		std::cin >> a >> b;
		isDancing[a] |= isDancing[b];
		isDancing[b] |= isDancing[a];
	}
	std::cout << std::accumulate(isDancing.begin(), isDancing.end(), 0,
		[](const int acc, const std::pair<std::string, bool>& e) {
			return acc + e.second;
		});
}