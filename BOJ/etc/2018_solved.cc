/*
	BOJ 2018

	등차수열의 합.
*/

#include <iostream>
using ll = long long;
int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	ll N;
	std::cin >> N;

	ll result = 0, k = 1;
	while (true)
	{
		ll min_sum = (k * (k + 1)) / 2;
		if (min_sum > N)
			break;
		result += ((N - min_sum) % k == 0);
		k++;
	}
	std::cout << result;
}
