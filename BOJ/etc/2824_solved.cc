/*
	BOJ 2824

	소인수분해
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using PFResult = std::unordered_map<int, int>;
constexpr const long long DIV = 10000000000;

void prime_factorize(int num, PFResult& result) {
	for (int prime = 2; prime * prime <= num; ++prime)
	{
		if (num == 1)
		{
			break;
		}

		int cnt = 0;
		while ((num % prime) == 0)
		{
			num /= prime;
			cnt++;
		}

		if (cnt > 0)
		{
			result[prime] += cnt;
		}
	}

	if (num > 1) {	// 이걸 몰랐네???
		result[num] += 1;
	}
}

PFResult prime_factorize_numbers(std::vector<int> const& nums) {
	PFResult result;

	for (auto const num : nums)
	{
		prime_factorize(num, result);
	}
	return result;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	int N, M;
	std::cin >> N;
	std::vector<int> A(N);
	for (auto& a : A)
		std::cin >> a;
	std::cin >> M;
	std::vector<int> B(M);
	for (auto& b : B)
		std::cin >> b;

	auto a_result = prime_factorize_numbers(A);
	auto b_result = prime_factorize_numbers(B);

	// combine
	for (auto& [val, cnt] : a_result)
	{
		cnt = std::min(cnt, b_result[val]);
	}

	// result calculation
	long long result = 1;
	for (auto const [val, cnt] : a_result)
	{
		for (int pow = 0; pow < cnt; ++pow)
		{
			result = (result * static_cast<long long>(val)) % DIV;
		}
	}

	// print
	std::string rstr = std::to_string(result);
	if (rstr.size() >= 10)
	{
		for (int i = 1; i < rstr.size(); ++i)
		{
			std::cout << rstr[i];
		}
	}
	else
	{
		std::cout << rstr;
	}
}
