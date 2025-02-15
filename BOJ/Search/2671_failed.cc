
#include <iostream>
#include <string>
#include <functional>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::string sound;
	std::cin >> sound;

	// functional
	auto prefixMatcher = [](const std::string &text, const std::string_view prefix, const int idx) -> bool
	{
		return ((idx + prefix.size() <= text.size()) && prefix == std::string_view(text.begin() + idx, text.begin() + idx + prefix.size()));
	};
	auto isPattern1 = std::bind(prefixMatcher, sound, "100", std::placeholders::_1);
	auto isPattern2 = std::bind(prefixMatcher, sound, "01", std::placeholders::_1);

	auto matchPattern1 = [&sound](int &idx) -> bool
	{
		int i = idx + 3;
		while (i < sound.size() && sound[i] == '0')
		{
			i++;
		}
		if (i >= sound.size())
			return false;
		else if (sound[i] == '1')
		{
			while (i < sound.size() && sound[i] == '1')
			{
				i++;
			}
			// find 01 or 100.... failed.
		}
		else
			return false;
		idx = i;
		return true;
	};
	auto matchPattern2 = [](int &idx) -> bool
	{
		idx += 2;
		return true;
	};

	// solve
	if ([&]() -> bool
		{
			int idx = 0;

			while (idx < sound.size())
			{
				if (isPattern1(idx))
				{
					if (!matchPattern1(idx))
						return false;
				}
				else if (isPattern2(idx))
				{
					if (!matchPattern2(idx))
						return false;
				}
				else
					return false;
			}
			return sound.size() != 0; }())
		std::cout << "SUBMARINE\n";
	else
		std::cout << "NOISE\n";
}
