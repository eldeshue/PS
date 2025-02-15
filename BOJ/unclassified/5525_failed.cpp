// 50Á¡.
#include <iostream>
#include <bitset>
#include <string>

using P = std::bitset<1000000>;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	P pn{ 0 }, s{ 0 }, mask{ 0 };
	std::string input;
	int N, M;

	std::cin >> N >> M >> input;
	for (int i = 0; i < M; ++i)
	{
		if (input[i] == 'I')
			s[i] = true;
		else
			s[i] = false;
	}
	// build pn
	for (int i = 0; i < N * 2 + 1; ++i)
	{
		if (!(i & 1))
			pn[i] = true;
		else
			pn[i] = false;
	}
	// build mask
	for (int i = 0; i < N * 2 + 1; ++i)
	{
		mask[i] = true;
	}
	// find result
	int result = 0;
	for (int i = 0; i < M + 1 - N; ++i)
	{
		if (((s >> i) & mask) == pn)
			result++;
	}
	std::cout << result;
}
