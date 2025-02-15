
#include <iostream>
#include <memory.h>

int N, S, M;
int delta_volume[51];
bool is_reachable[51][1001];

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(delta_volume, 0, sizeof(delta_volume));
	memset(is_reachable, 0, sizeof(is_reachable));

	std::cin >> N >> S >> M;
	for (int i = 1; i <= N; ++i)
		std::cin >> delta_volume[i];
	is_reachable[0][S] = true;
	for (int num_song = 1; num_song <= N; ++num_song)
	{
		for (int cur_vol = 0; cur_vol <= M; ++cur_vol)
		{
			if (is_reachable[num_song - 1][cur_vol])
			{
				if (cur_vol + delta_volume[num_song] <= M)
				{
					is_reachable[num_song][cur_vol + delta_volume[num_song]] = true;
				}
				if (cur_vol - delta_volume[num_song] >= 0)
				{
					is_reachable[num_song][cur_vol - delta_volume[num_song]] = true;
				}
			}
		}
	}
	int max_vol = -1;
	for (int i = 0; i <= M; ++i)
	{
		if (is_reachable[N][i])
			max_vol = i;
	}
	std::cout << max_vol;
}