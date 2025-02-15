
#include <iostream>
#include <vector>
#include <cmath>

using ll = long long;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	ll min, max;
	std::cin >> min >> max;
	ll numSNN = max - min + 1;
	std::vector<bool> isSNN(numSNN, true); // is SquareNoNo

	// erathosthenese's filter
	const ll rootMax = std::sqrt(max);
	for (ll rootDiv = 2; rootDiv <= rootMax; ++rootDiv) // sqrt(max)
	{
		const ll div = rootDiv * rootDiv;
		ll idx = (min / div) * div - min;
		if (idx < 0)
			idx += div;
		for (; idx <= max - min; idx += div) // else, erase
		{
			if (isSNN[idx])
			{
				isSNN[idx] = false;
				numSNN--;
			}
		}
	}
	std::cout << numSNN;
}
