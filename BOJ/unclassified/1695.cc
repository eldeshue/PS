
/*

	boj 1695, 펠린드롬 만들기

	주어진 수열을 펠린드롬으로 만드는 최소 개수의 수를 구하기.
	최소 개수의 수이므로 최적화 문제임.

	펠린드롬이란 무엇인가? 바로 대칭을 이루는 수열이다.
	대칭이라 함은 대칭을 이루는 축이 있음이다.
	대칭 축을 찾으면, 그 축을 중심으로 하여 반대편이 대칭을 이룰 가능성이 있는지 탐색

	최장 공통 부분수열을 자신과 뒤집어진 자신에 대해서 수행하고
	최장 공통 부분수열의 길이를 기존 문자열의 길이에서 빼면 그것이 답이다.

*/
#include <iostream>
#include <array>
#include <memory.h>

int N;
std::array<int, 5000> arr;
std::array<int, 5000> reverse;
int cache[2][5001];

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(cache, 0, sizeof(cache));

	std::cin >> N;
	for (int i = 0; i < N; ++i)
		std::cin >> arr[i];
	for (int i = 0; i < N; ++i)
		reverse[i] = arr[N - 1 - i];
	// DP
	for (int idx = 0; idx < N; ++idx)
	{
		for (int ridx = 0; ridx < N; ++ridx)
		{
			int cur = 1 & idx;
			int next = 1 - (1 & idx);
			if (arr[idx] == reverse[ridx])
				cache[next][ridx + 1] = cache[cur][ridx] + 1;
			else
				cache[next][ridx + 1]
					= std::max(cache[cur][ridx + 1], cache[next][ridx]);
		}
	}
	// result
	std::cout << N - cache[N][N];
}
