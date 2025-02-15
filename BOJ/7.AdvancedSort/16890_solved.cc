
#include <iostream>
#include <algorithm>
#include <string>

/*
	서로가 서로의 상태를 모두 알고 있다고 가정한다.
*/

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::string koo, cube;	 // abzzz aaaab -> abbza
	std::cin >> koo >> cube; // abzzz baaaa ->
	const int N = koo.size();
	// n log n, limit
	std::sort(koo.begin(), koo.end(), std::less<char>());
	std::sort(cube.begin(), cube.end(), std::greater<char>());
	std::string result(N, '?');
	auto kooItr = koo.begin();
	auto kooRItr = koo.begin() + (N + 1) / 2 - 1; // 써야 하는 문자 중 가장 큰 값
	auto cubeItr = cube.begin();
	auto cubeRItr = cube.begin() + N / 2 - 1; // 써야 하는 문자 중 가장 작은
	auto rFront = result.begin();
	auto rBack = result.rbegin();
	for (int turn = 0; turn < N; ++turn)
	{
		if (turn & 1) // cube turn, keep result big
		{
			if (*cubeItr <= *kooItr)
				*rBack++ = *cubeRItr--;
			else
				*rFront++ = *cubeItr++; // 정방향
		}
		else // koo turn
		{
			if (*kooItr >= *cubeItr)
				*rBack++ = *kooRItr--;
			else
				*rFront++ = *kooItr++; // 정방향
		}
	}
	std::cout << result;
}
