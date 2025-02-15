
#include <iostream>
#include <cmath>

long long s, N, K, R1, R2, C1, C2;

bool is_mid(long long quot)
{
	long long offset = (N - K) / 2;
	if (offset <= quot && quot < offset + K)
	{
		return true;
	}
	return false;
}

bool is_black(long long y, long long x, long long cur_div)
{
	if (cur_div == 0)
	{
		std::cout << '0';
		return false;
	}
	if (is_mid(y / cur_div) && is_mid(x / cur_div))
	{
		std::cout << '1';
		return true;
	}
	else
	{
		return is_black(y % cur_div, x % cur_div, cur_div / N);
	}
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::cin >> s >> N >> K >> R1 >> R2 >> C1 >> C2;
  for (long long y = R1; y <= R2; ++y)
  {
	for (long long x = C1; x <= C2; ++x)
	{
		is_black(y, x, std::pow(N, s - 1));
	}
	std::cout << '\n';
  }
}
