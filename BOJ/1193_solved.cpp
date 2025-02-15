
#include <iostream>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int x, n;
	std::cin >> x;
	for (n = 1; n < x; ++n)
	{
		x -= n;
	}
	// nÀÌ Â¦¼ö´Â ÁÂÇÏÇâ, È¦¼ö´Â ¿ì»óÇâ
	if (n & 1)	// È¦¼ö
	{
		std::cout << n + 1 - x << '/' << x;
	}
	else // Â¦¼ö
	{
		std::cout << x << '/' << n + 1 - x;
	}
}