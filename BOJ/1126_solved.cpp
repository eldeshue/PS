
/*
BOJ 1126, 같은 탑

문제의 이름에서 힌트를 얻어야 함. 같은 탑 -> 두 탑의 구분이 불필요함.

두 탑을 서로 구분할 필요가 없음. -> 중요한 것은 두 탑의 높이 차이임.

cache[i번 물체][두 탑의 gap] = 지금까지 버리지 않고 사용한 물체 총 합, 최대값

cache의 값을 A, 직사각형의 높이를 B

그냥 j는 해당 블럭을 버리는 방향

j + B[i] 는 이전 탑의 높이차를 j로 줄이는 방향, 즉 두 탑 중 작은 쪽에다 쌓음

abs( j - B[i] )는 이전 탑의 높이 차이를 j로 늘리는 방향, 즉 두 탑 중 큰 쪽에 쌓음

A[i][j] = max(	
		A[ i-1 ][ j ],					// B[i]를 버리거나
		A[ i-1 ][ j +  B[i]  ] ,		// B[i]를 더 낮은 탑에 쌓거나
		A[ i-1 ][ abs( j - B[i] ) ]		// B[i]를 더 높은 탑에 쌓거나
			)
*/
#include <iostream>
#include <array>

using Cache = std::array<int, 500001>;
Cache c1, c2;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::fill(c1.begin(), c1.end(), -1);
	std::fill(c2.begin(), c2.end(), -1);
	c1[0] = 0;
	c2[0] = 0;
	Cache* pprevCache = &c1;
	Cache* pcurCache = &c2;

	int N, curVal;
	std::cin >> N;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> curVal;
		// tabulation
		for (int curGap = 0; curGap <= 500000 - curVal; ++curGap)
		{
			const int prevGap1 = curGap + curVal;	// 이전 gap이 더 크다
			const int prevGap2 = std::abs(curGap - curVal);	// 이전 gap이 더 작다
			(*pcurCache)[curGap] = (*pprevCache)[curGap];	// curVal을 버리는 경우
			if ((*pprevCache)[prevGap1] != -1)
			{
				// 두 탑의 차이를 좁히는 경우
				(*pcurCache)[curGap] = std::max((*pcurCache)[curGap],
					(*pprevCache)[prevGap1] + curVal);
			}
			if ((*pprevCache)[prevGap2] != -1)
			{
				// 두 탑의 차이를 벌리는 경우
				(*pcurCache)[curGap] = std::max((*pcurCache)[curGap],
					(*pprevCache)[prevGap2] + curVal);
			}
		}
		std::swap(pprevCache, pcurCache);
	}
	if ((*pprevCache)[0] == 0)	// impossible, 차이가 0으로 좁혀진 적이 없음
		std::cout << -1;
	else
		std::cout << (*pprevCache)[0] / 2;	// 투자한 비용이 같을 것이므로, 2로 나눔
}