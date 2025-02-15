
#include <iostream>
#include <string>

bool is_aeiou(char c)
{
	if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
		return true;
	c += 32;
	if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
		return true;
	return false;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::string in;
	std::getline(std::cin, in);
	for (; in != "#"; std::getline(std::cin, in))
	{
		int count = 0;
		for (const char& c : in)
		{
			if (is_aeiou(c))
				count++;
		}
		std::cout << count << '\n';
	}
}
