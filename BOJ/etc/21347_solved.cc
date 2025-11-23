/*
	BOJ 21347
*/
#include <iostream>
#include <unordered_map>
#include <string>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::string normal_text, doubled_text;
	std::getline(std::cin, normal_text);
	std::getline(std::cin, doubled_text);

	std::unordered_map<char, int> norm_freq, doubl_freq;
	for (char const c : normal_text)
		norm_freq[c]++;
	for (char const c : doubled_text)
		doubl_freq[c]++;

	auto is_double = [&](char const c) -> bool {
		if (norm_freq.contains(c))
		{
			return (norm_freq[c] != doubl_freq[c]);
		}
		return false;
		};

	std::string result;
	for (char c = 'a'; c <= 'z'; ++c)
	{
		if (is_double(c))
			result.push_back(c);
	}
	if (is_double(' '))
	{
		result.push_back(' ');
	}
	std::cout << result;
}
