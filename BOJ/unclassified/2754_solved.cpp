
#include <iostream>
#include <string>
#include <map>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::map<std::string, std::string> score_map;
	score_map.insert(std::make_pair("A+", "4.3"));
	score_map.insert(std::make_pair("A0", "4.0"));
	score_map.insert(std::make_pair("A-", "3.7"));
	score_map.insert(std::make_pair("B+", "3.3"));
	score_map.insert(std::make_pair("B0", "3.0"));
	score_map.insert(std::make_pair("B-", "2.7"));
	score_map.insert(std::make_pair("C+", "2.3"));
	score_map.insert(std::make_pair("C0", "2.0"));
	score_map.insert(std::make_pair("C-", "1.7"));
	score_map.insert(std::make_pair("D+", "1.3"));
	score_map.insert(std::make_pair("D0", "1.0"));
	score_map.insert(std::make_pair("D-", "0.7"));
	score_map.insert(std::make_pair("F", "0.0"));

	std::string grade;
	std::cin >> grade;
	std::cout << score_map[grade] << '\n';
}