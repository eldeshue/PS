
#include <iostream>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int a, b, c, d, e, f;
	std::cin >> a >> b >> c >> d;
	e = a + b + c + d;
	std::cin >> a >> b >> c >> d;
	f = a + b + c + d;
	std::cout << std::max(e, f);
}