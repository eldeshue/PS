
// fast IO
#include <iostream>
#include <string>
#include <map>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::map<std::string, std::string> m;
	m.insert(std::make_pair("Algorithm", "204"));
	m.insert(std::make_pair("DataAnalysis", "207"));
	m.insert(std::make_pair("ArtificialIntelligence", "302"));
	m.insert(std::make_pair("CyberSecurity", "B101"));
	m.insert(std::make_pair("Network", "303"));
	m.insert(std::make_pair("Startup", "501"));
	m.insert(std::make_pair("TestStrategy", "105"));

	int N;
	std::cin >> N;
	for (int i = 0; i < N; ++i)
	{
		std::string input;
		std::cin >> input;
		std::cout << m[input] << '\n';
	}
}