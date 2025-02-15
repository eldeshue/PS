
#include <iostream>
#include <string>
#include <memory.h>

bool set[21];

void add(int x)
{
	set[x] = true;
}

void remove(int x)
{
	set[x] = false;
}

void check(int x)
{
	std::cout << set[x] << '\n';
}

void toggle(int x)
{
	set[x] = !set[x];
}

void all()
{
	memset(set, 1, sizeof(set));
}

void empty()
{
	memset(set, 0, sizeof(set));
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cout.tie(nullptr);
	std::cin.tie(nullptr);

	int numQuery, x;
	std::string query;
	std::cin >> numQuery;
	for (int i = 0; i < numQuery; ++i)
	{
		std::cin >> query;
		if (query == "add")
		{
			std::cin >> x;
			add(x);
		}
		else if (query == "remove")
		{
			std::cin >> x;
			remove(x);
		}
		else if (query == "check")
		{
			std::cin >> x;
			check(x);
		}
		else if (query == "toggle")
		{
			std::cin >> x;
			toggle(x);
		}
		else if (query == "all")
		{
			all();
		}
		else if (query == "empty")
		{
			empty();
		}
	}
}