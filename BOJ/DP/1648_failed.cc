
/*
	BOJ 1648 격자판 채우기

	tiling problem의 궁극 version

	===================================================

	<비용 분석>

	이전 row의 상태를 bit set으로 표현할 수 있음. row의 길이가 14가 최대이기 때문임.
	즉, 한 row가 가질 수 있는 최대 상태는 2^14, 4000여개임.
	여기서 문제는 이전 row에서 현재 row의 상태를 만드는 방법임.
	2x1 타일이므로, 한 타일을 눕히거나 세워서 넣을 수 있음.
	이전 row에 새로운 타일의 조합을 얹을 것인데,
	기존 상태 & 얹는 상태 > 0이면 안됨.
	14 4000 4000 -> 가능할 것으로 보임.

	1 <= N, M <= 14
	time : O(N * 2 ^ 2M) -> M must be smaller one, symmetricism
	space : 2^2M + N * 2^M

	===================================================================

	bit masking을 up word와 down word로 나눠서 수행함.

	일단 패턴과 그에 따른 가짓수를 colum 뱡향 타일링 문제를 풀어서 구함(bitmasking).

	종방향 dp를 통해서 얻은 값을 테이블에 저장 pattern[whole pattern] = count

	이후 이 pattern 배열을 기준으로 row방향 dp를 수행, 실제 가짓수를 count함.

	cur dword pattern = ~(prev upword pattern)

	cache[next dword pattern] += pattern[cur pattern] * cache[cur dword pattern]

	====================================================================

	failed. 완전히 잘못된 접근이었다.

	문제는 위 방식으로 문제를 풀면, 필연적으로 중복이 발생하는데, 이 중복을 처리하는 생각을 못했다.

	타일링 문제를 완전히 잘못 이해했다.
*/

#include <iostream>
#include <algorithm>
#include <array>

using Pattern = int;
constexpr const int NOT_VISITED = -1;
constexpr const int MAX_LEN = 14;
constexpr const int DIV = 9901;
constexpr const int LOW_MASK = (1 << MAX_LEN) - 1;
constexpr const int HIGH_MASK = LOW_MASK << MAX_LEN;
inline Pattern constexpr GET_LOW_PATTERN(Pattern const whole)
{
	return LOW_MASK & whole;
}
inline Pattern constexpr GET_HIGH_PATTERN(Pattern const whole)
{
	return (HIGH_MASK & whole) >> MAX_LEN;
}
inline Pattern constexpr GET_WHOLE_PATTERN(Pattern const high, Pattern const low)
{
	return (high << MAX_LEN) | low;
}

constexpr const int HORIZONTAL_TILE = 3;
constexpr const int VERTICAL_TILE = GET_WHOLE_PATTERN(1, 1);
inline bool is_sub_pattern(Pattern const origin, Pattern const sub)
{
	return (origin & sub) == sub;
}

std::array<int, 1 << (MAX_LEN << 1)> pattern;
std::array<std::array<int, 1 << MAX_LEN>, MAX_LEN + 1> cache;

// memoization
int fill_pattern(int const end, Pattern const p)
{
	// base case already included
	// if p == 0, return 1
	if (pattern[p] != NOT_VISITED)	// cache hit
	{
		return pattern[p];
	}
	else
	{
		pattern[p] = 0;
		for (int c = 0; c < end - 1; ++c)	// horizontal low
		{
			Pattern erase = HORIZONTAL_TILE << c;
			if (is_sub_pattern(p, erase))
				pattern[p] = (pattern[p] + fill_pattern(end, p - erase)) % DIV;
		}
		for (int c = 0; c < end - 1; ++c)	// horizontal high
		{
			Pattern erase = HORIZONTAL_TILE << (c + MAX_LEN);
			if (is_sub_pattern(p, erase))
				pattern[p] = (pattern[p] + fill_pattern(end, p - erase)) % DIV;
		}
		for (int c = 0; c < end; ++c)	// vertical
		{
			Pattern erase = VERTICAL_TILE << c;
			if (is_sub_pattern(p, erase))
				pattern[p] = (pattern[p] + fill_pattern(end, p - erase)) % DIV;
		}
		return pattern[p];
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	int N, M;
	std::cin >> N >> M;
	if (N < M)
		std::swap(N, M);	// problem status is symmetrical

	if ((N * M) & 1)
	{
		std::cout << 0 << '\n';	// sum of tiled area must be even.
		return 0;
	}
	if (M == 1)	// logical exception, single line
	{
		std::cout << 1 << '\n';
		return 0;
	}

	// solve colum, fill pattern
	std::fill(pattern.begin(), pattern.end(), NOT_VISITED);
	pattern[0] = 1;	// base case
	fill_pattern(M, GET_WHOLE_PATTERN((1 << M) - 1, (1 << M) - 1));

	// dummy data for test
	{
		// diagonal
		pattern[0] = 1;
		pattern[GET_WHOLE_PATTERN(1, 1)] = 1;
		pattern[GET_WHOLE_PATTERN(2, 2)] = 1;
		pattern[GET_WHOLE_PATTERN(3, 3)] = 2;
		pattern[GET_WHOLE_PATTERN(4, 4)] = 1;
		pattern[GET_WHOLE_PATTERN(5, 5)] = 1;
		pattern[GET_WHOLE_PATTERN(6, 6)] = 2;
		pattern[GET_WHOLE_PATTERN(7, 7)] = 3;

		// non diagonal
		pattern[GET_WHOLE_PATTERN(0, 3)] = 1;
		pattern[GET_WHOLE_PATTERN(3, 0)] = 1;
		pattern[GET_WHOLE_PATTERN(0, 6)] = 1;
		pattern[GET_WHOLE_PATTERN(6, 0)] = 1;
		pattern[GET_WHOLE_PATTERN(1, 7)] = 1;
		pattern[GET_WHOLE_PATTERN(7, 1)] = 1;
		pattern[GET_WHOLE_PATTERN(2, 7)] = 1;
		pattern[GET_WHOLE_PATTERN(7, 2)] = 1;
		pattern[GET_WHOLE_PATTERN(3, 6)] = 1;
		pattern[GET_WHOLE_PATTERN(6, 3)] = 1;
		pattern[GET_WHOLE_PATTERN(4, 7)] = 1;
		pattern[GET_WHOLE_PATTERN(7, 4)] = 1;
	}

	// debug
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			std::cout << pattern[GET_WHOLE_PATTERN(i, j)] << ' ';
		}
		std::cout << '\n';
	}

	// solve row, bitmasking dp
	std::for_each(cache.begin(), cache.end(), [](auto& cache_line) {
		std::fill(cache_line.begin(), cache_line.end(), 0);
		});
	Pattern const end = 1 << M;
	cache[0][0] = 1;
	for (int r = 0; r < N; ++r)	// 14
	{
		for (Pattern cur = 0; cur < end; ++cur)	// cur pattern, 2^14
		{
			for (Pattern next = 0; next < end; ++next)	// next pattern, 2^14
			{
				Pattern new_layer = GET_WHOLE_PATTERN(next, (~cur) & (end - 1));
				if (pattern[new_layer] > 0)
					cache[r + 1][next] = (cache[r + 1][next] + (cache[r][cur] * pattern[new_layer]) % DIV) % DIV;
			}
		}
	}

	// print
	for (int i = 0; i <= N; ++i)
	{
		for (int j = 0; j < end; ++j)
			std::cout << cache[i][j] << ' ';
		std::cout << '\n';
	}
	std::cout << cache[N][end - 1];
}

