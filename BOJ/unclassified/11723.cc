
#include <iostream>
#include <string>

int n, x, set = 0;

inline void add()
{
	std::cin >> x;
	set |= (1 << x);
}

inline void remove()
{
	std::cin >> x;
	set &= ~(1 << x);
}

inline void check()
{
	std::cin >> x;
	std::cout << static_cast<bool>(set & (1 << x)) << '\n';
}

inline void toggle()
{
	std::cin >> x;
	x ^= (1 << x);
}

inline void all()
{
	set = -1;
}

inline void empty()
{
	set = 0;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::string str;
	std::cin >> n;
	for (int i = 0; i < n; ++i)
	{
		std::cin >> str;
		if (str == "add")
			add();
		else if (str == "remove")
			remove();
		else if (str == "check")
			check();
		else if (str == "toggle")
			toggle();
		else if (str == "all")
			all();
		else
			empty();
	}
}
