
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

inline void print_(int n)
{
	for (int i = 0; i < n; ++i)
		std::cout << '_';
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	
	int N, M, cnt, remainder;
	std::cin >> N >> M;
	std::vector<std::string> vecStr(N);
	for (int i = 0; i < N; ++i)
	{
		std::cin >> vecStr[i];
		M -= vecStr[i].size();
	}
	cnt = N - 1;
	for (int i = 0; i < N - 1; ++i)
	{
		std::cout << vecStr[i];
		int sum;
		if ('a' <= vecStr[i + 1][0] && M % cnt != 0)
			sum = M / cnt + 1;
		else
			sum = M / cnt;
		print_(sum);
		M -= sum;
		cnt--;
	}
	std::cout << vecStr[N - 1];
}