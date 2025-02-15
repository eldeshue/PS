
#include <iostream>
#include <vector>

using ll = long long;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	std::cin >> N;
	std::vector<ll> dists(N - 1);
	for (auto& d : dists)
		std::cin >> d;
	std::vector<ll> costs(N);
	for (auto& c : costs)
		std::cin >> c;
	ll result = 0, curCost = 2e9;
	for (int i = 0; i < N - 1; ++i)
	{
		curCost = std::min(curCost, costs[i]);
		result += curCost * dists[i];
	}
	std::cout << result;
}