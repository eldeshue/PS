
#include <iostream>
#include <string>
#include <unordered_map>

using ll = long long;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::unordered_map<std::string, std::pair<ll, ll>> resistanceTable
		{
			{"black", {0, 1}},
			{"brown", {1, 10}},
			{"red", {2, 100}},
			{"orange", {3, 1000}},
			{"yellow", {4, 10000}},
			{"green", {5, 100000}},
			{"blue", {6, 1000000}},
			{"violet", {7, 10000000}},
			{"grey", {8, 100000000}},
			{"white", {9, 1000000000}}
		};

	ll result = 0;
	std::string input;
	std::cin >> input;
	result = resistanceTable[input].first;
	std::cin >> input;
	result = 10 * result + resistanceTable[input].first;
	std::cin >> input;
	std::cout << result * resistanceTable[input].second;
}