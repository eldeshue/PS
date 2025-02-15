
#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <vector>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	int nPeople, nParty, nTruth, result = 0;
	std::set<int> truthTable;
	std::string test;
	std::cin >> nPeople >> nParty >> nTruth;
	for (int i = 0; i < nTruth; ++i)
	{
		int temp;
		std::cin >> temp;
		truthTable.insert(temp);
	}
	for (int i = 0; i < nParty; ++i)
	{
		int party_people_num, tgt;
		std::cin >> party_people_num;
		for(int i = 0; i < party_people_num; ++i)
		{
			std::cin >> tgt;
			if (truthTable.find(tgt) != truthTable.end())
			{
				result--;
				break;
			}
		}
		result++;
	}
	std::cout << result;
}