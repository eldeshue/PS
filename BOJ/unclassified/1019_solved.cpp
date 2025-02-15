
#include<iostream>
#include <array>

using ull = unsigned long long;
using Stat = std::array<ull, 10>;

std::ostream& operator<<(std::ostream& os, Stat s)
{
	for (int i = 0; i < 10; ++i)
		os << s[i] << ' ';
	return os;
}

Stat operator*(const Stat& s, const ull n)
{
	Stat a;
	for (int i = 0; i < 10; ++i)
		a[i] = s[i] * n;
	return a;
}

Stat operator+(const Stat& s1, const Stat& s2)
{
	Stat a;
	for (int i = 0; i < 10; ++i)
		a[i] = s1[i] + s2[i];
	return a;
}

// g(k), [0, 10 ^ k)에 대하여
/*
	g(0) = {0 0 0 0 0 0 0 0 0 0}
	g(1) = {1 1 1 1 1 1 1 1 1 1}
	g(2) = {20 20 20 20 20 20 20 20 20 20}
	g(3) = {300 300 300 300 300 300 300 300 300 300}

	F(9) = {0 1 1 1 1 1 1 1 1 1}
	F(99) = {10 20 20 20 20 20 20 20 20 20}
	F(999) = {200 300 300 300 300 300 300 300 300 300}
	-> erase leading zero from g to get F
*/
Stat g(ull k)
{
	Stat s = { 0, };
	if (k == 0)
		return s;
	for (int i = 0; i < 10; ++i)
	{
		s[i] = k * std::pow(10, k - 1);
	}
	return s;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	Stat result = {0, };
	Stat count = {0, };

	std::string input;
	std::cin >> input;
	for (int i = 0; i < input.size() / 2; ++i)
	{
		std::swap(input[i], input[input.size() - 1 - i]);
	}
	for (int pos = input.size() - 1; pos >= 0; --pos)
	{
		result = result
			+ g(pos) * (input[pos] - '0')
			+ count * std::pow(10, pos) * (input[pos] - '0');
		for (int i = 0; i < input[pos] - '0'; ++i)
		{
			result[i] += std::pow(10, pos);
		}
		count[input[pos] - '0']++;
	}
	for (int i = 0; i < 10; ++i)
	{
		result[i] += count[i];
	}
	// erase leading zero
	for (int i = 0; i < input.size(); ++i)
	{
		result[0] -= std::pow(10, i);
	}
	std::cout << result;
}