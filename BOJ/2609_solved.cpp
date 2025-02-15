
#include <iostream>

int euclid(int s, int b)
{
	int mod = 1;
	while (mod != 0)
	{
		mod = b % s;
		b = s;
		s = mod;
	}
	return b;
}

int euclid_recurse(int s, int b)
{
	if (s == 0)
	{
		return b;
	}
	return euclid_recurse(b % s, s);
}


int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int a, b, GCD, LCM;
	std::cin >> a >> b;
	GCD = euclid(std::min(a, b), std::max(a, b));
	LCM = a * b / GCD;
	std::cout << GCD << '\n' << LCM << '\n';
}