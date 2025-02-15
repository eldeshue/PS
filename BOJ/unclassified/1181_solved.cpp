/*
#include <iostream>
#include <string>
#include <set>
#include <algorithm>

struct strCmp {
	bool operator()(const std::string& l, const std::string& r) const
	{
		if (l.length() == r.length())
		{
			return l < r;
		}
		else
		{
			return l.length() < r.length();
		}

	}
};

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	int n;
	std::cin >> n;
	std::set<std::string, strCmp> data;
	std::string temp;
	for (int i = 0; i < n; ++i)
	{
		std::cin >> temp;
		data.insert(temp);
	}
		
	for (const auto& elem : data)
	{
		std::cout << elem << "\n";
	}
}
*/
