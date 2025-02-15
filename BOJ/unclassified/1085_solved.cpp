
#include <iostream>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int x, y, w, h, xr, yr;
	std::cin >> x >> y >> w >> h;
	xr = w - x;
	x = ((xr > x) ? x : xr);
	yr = h - y;
	y = ((yr > y) ? y : yr);
	std::cout << ((y > x) ? x : y);
}