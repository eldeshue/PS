
#include <iostream>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int sh, sm, ss, eh, em, es, dh, dm, ds;
	for (int i = 0; i < 3; ++i)
	{
		std::cin >> sh >> sm >> ss >> eh >> em >> es;
		dh = eh - sh;
		if (em < sm)
		{
			dh--;
			em += 60;
		}
		dm = em - sm;
		if (es < ss)
		{
			if (dm == 0)
			{
				dh--;
				dm += 60;
			}
			dm--;
			es += 60;
		}
		ds = es - ss;
		std::cout << dh << ' ' << dm << ' ' << ds << '\n';
	}
}