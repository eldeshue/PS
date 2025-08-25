/*
	BOJ 1648

	bitmasking + tabulation dp

	=======================================
	가능한 수평 타일 조합을 구해서 미리 저장함.

	이후 층을 쌓아 올리는데, 수평 타일 조합을 제외한 모든 부분은 수직 타일로 생각한다.
*/
#include <array>
#include <deque>
#include <iostream>

int constexpr const DIV = 9901;
int constexpr const HORIZONTAL_TILE = 3;
std::array<bool, 1 << 14> is_fillable;
std::array<std::array<int, 1 << 14>, 2> cache;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	std::fill(is_fillable.begin(), is_fillable.end(), false);
	std::fill(cache[0].begin(), cache[0].end(), 0);
	std::fill(cache[1].begin(), cache[1].end(), 0);

	// input
	int N, M;
	std::cin >> N >> M;	// N : row, M : col

	if (N < M)
		std::swap(N, M);

	// M is under 15
	int const MAX = 1 << M;
	int const MASK = MAX - 1;

	for (int stat = 0; stat < MAX; ++stat)
	{
		if (true)
		{
			is_fillable[stat] = true;
		}
	}

	// 수평 타일 조합의 수 구하기
	std::deque<int> horizontal_layers(1, 0);
	for (int pos = 0; pos < M - 1; ++pos)
	{
		int const end = horizontal_layers.size();
		for (int i = 0; i < end; ++i)
		{
			if ((horizontal_layers[i] & (HORIZONTAL_TILE << pos)) == 0)
			{
				horizontal_layers.push_back(horizontal_layers[i] | (3 << pos));
			}
		}
	}

	// tabulation
	// 앞서 구한 layer를 쌓아 올린다.
	int cur_pos = 0, next_pos = 1;
	cache[cur_pos][0] = 1;
	for (int i = 0; i < N; ++i)
	{
		for (int cur_stat = 0; cur_stat < MAX; ++cur_stat)
		{
			// cur_stat : 이전 층에 쌓은 수직 타일의 결과, 튀어나온 부분
			for (auto const hlayer : horizontal_layers)
			{
				// 수평 layer와 겹치면 안됨.
				if (cur_stat & hlayer)
					continue;
				// 수평 layer를 덮고 남은 부분은 수직 타일로 덮음
				// 지금 수직 타일로 덮는 부분이 다음 layer에 튀어나온 부분
				int const next_stat = MASK & ~(cur_stat | hlayer);
				cache[next_pos][next_stat] =
					(cache[next_pos][next_stat]
						+ cache[cur_pos][cur_stat]) % DIV;
			}
		}
		std::swap(cur_pos, next_pos);
		std::fill(cache[next_pos].begin(), cache[next_pos].end(), 0);
	}

	// debug
	std::cout << cache[cur_pos][0];
}