
// �賶����, ��� C�̻��� ���ϱ� ���� �ּҰ�
#include <iostream>
#include <memory.h>

using uint = unsigned int;

int cost[20][2];	// cost , people
uint cache[20][1001];	// cache[��ģ ����][�ο���] = minimum cost
						// C�̻��� �ϳ��� ���ļ� ��������

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(cache, -1, sizeof(cache));

	int C, N;
	std::cin >> C >> N;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> cost[i][0] >> cost[i][1];
	}
	// init
	for (int i = 0; ; ++i)
	{
		if (i * cost[0][1] >= C)
		{
			cache[0][C] = i * cost[0][0];
			break;
		}
		cache[0][i * cost[0][1]] = i * cost[0][0];
	}
	// DP
	for (int cur_city = 1; cur_city < N; ++cur_city)
	{
		cache[cur_city][0] = 0;
		for (int cur_people = 0; cur_people < C; ++cur_people)
		{
			cache[cur_city][cur_people] = std::min(cache[cur_city][cur_people],
				cache[cur_city - 1][cur_people]);
			if (cache[cur_city][cur_people] == -1)
				continue;
			uint next_people = cur_people + cost[cur_city][1];
			if (next_people > C)
				next_people = C;
			cache[cur_city][next_people] 
				= std::min(cache[cur_city][next_people], 
				std::min(cache[cur_city - 1][next_people], 
				cache[cur_city][cur_people] + cost[cur_city][0])
			);
		}
	}
	std::cout << cache[N - 1][C];
}