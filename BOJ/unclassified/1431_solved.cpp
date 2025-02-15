
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

int cal_num_guitar(const std::string& g)
{
	int result = 0;
	for (const char &cur_char : g)
	{
		if ('0' <= cur_char && cur_char <= '9')
		{
			result += cur_char - '0';
		}
	}
	return result;
}

bool cmp_guitar(const std::string& g1, const std::string& g2)
{
	int g_val1, g_val2;
	if (g1.size() != g2.size())	// 번호의 길이
	{
		return (g1.size() < g2.size()); // 짧은 쪽이 먼저, 즉 오름차순
	}
	g_val1 = cal_num_guitar(g1);	// 숫자의 합
	g_val2 = cal_num_guitar(g2);
	if (g_val1 != g_val2)
	{
		return (g_val1 <= g_val2); // 값이 작은쪽이 먼저, 즉 오름차순
	}
	return (g1 < g2);	// 사전순 정렬, 오름차순
}

std::vector<std::string> guitars;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	std::string input;
	std::cin >> N;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> input;
		guitars.push_back(input);
	}
	std::sort(guitars.begin(), guitars.end(), cmp_guitar);
	for (const std::string& cur_g : guitars)
	{
		std::cout << cur_g << '\n';
	}
}