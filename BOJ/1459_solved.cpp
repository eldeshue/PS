
#include <iostream>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	long long s, l, block_time, diag_time, total = 0;
	std::cin >> s >> l >> block_time >> diag_time;
	if (s > l)
		std::swap(s, l);
	if (diag_time < 2 * block_time)
	{
		l -= s;
		total += s * diag_time;
		if (diag_time < block_time)
		{
			total += (l - (l % 2)) * diag_time + (l % 2) * block_time;
		}
		else
		{
			total += l * block_time;
		}
	}
	else
	{
		total = (s + l) * block_time;
	}
	std::cout << total;
}