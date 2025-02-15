
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>

long long int numField;
std::map<long long int, long long int> factions;
std::vector<std::pair<long long int, long long int>> buffer;

bool cmp(const std::pair<long long int, long long int>& p1, const std::pair<long long int, long long int>& p2)
{
	return p1.second > p2.second;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	long long int numSoldiers, s;
	std::string input;
	std::cin >> numField;
	for (long long int i = 0; i < numField; ++i)
	{
		factions.clear();
		buffer.clear();
		std::cin >> numSoldiers;
		for (long long int i = 0 ; i < numSoldiers; ++i)
		{
			std::cin >> s;
			if (factions.find(s) != factions.end())
			{
				factions[s]++;
			}
			else
			{
				factions.insert(std::make_pair(s, 1)); // 간접 참조 에러 주의
			}
		}
		// value 크기 순서로 정렬
		for (const auto& elem : factions)
		{
			buffer.push_back(elem);
		}
		std::sort(buffer.begin(), buffer.end(), cmp);
		long long int result = buffer.front().first;
		long long int value = buffer.front().second;
		
		// 가장 큰 value가 과반인지 확인하고 출력
		if (value > (numSoldiers / 2))
		{
			std::cout << result << "\n";
		}
		else
		{
			std::cout << "SYJKGW" << "\n";
		}
	}
}
