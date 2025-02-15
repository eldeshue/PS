
#include <iostream>
#include <vector>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, Q, sum = 0;
	std::cin >> N;
	std::vector<int> weights(N);
	for (int& w : weights)
	{
		std::cin >> w;
		sum += w;
	}
	std::vector<bool> isMeasurable(55000 + 1, false);
	isMeasurable[0] = true;

	// tabulation
	for (int const w : weights)
	{
		for (int i = sum - w; i >= 0; --i)
		{
			if (isMeasurable[i])
			{
				isMeasurable[i + w] = true;
			}
		}
	}

	// query handling
	std::cin >> Q;
	while (Q--)
	{
		int q;
		std::cin >> q;
		bool result = false;
		for (int w = 0; w <= 15000; ++w)
		{
			if (isMeasurable[w] && isMeasurable[q + w])
				result = true;
		}
		if (result)
			std::cout << "Y ";
		else
			std::cout << "N ";
	}
}