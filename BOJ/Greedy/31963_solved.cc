/*
	BOJ 31963

	실제 값을 prefix삼고, 곱한 횟수(shift 횟수)를 따로 저장
	직전 값과 비교 과정에서 shift 횟수를 optimal하게 조정하였습니다.

	시간 복잡도는 O(N log (max A))인데, log (max A)가 대략 20이므로,
	O(N)이라 해도 될 듯.

	상당히 특이한 case가 있어서 최종 횟수 계산에서 overflow가 날 수 있는데,
	바로 모든 값이 1식 낮아지는 내림차순인 경우임.
	이 경우 이전에 shift한 횟수 * 2배 만큼 shift가 필요해지는데,
	이 경우에는 20 * N^2이 되어버려서 int 범위를 초과하게 됨.
*/
#include <iostream>
#include <vector>
#include <array>
#include <numeric>

using ll = long long;
using pii = std::array<ll, 2>;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	std::cin >> N;
	std::vector<pii> buffer(N, { 0, 0 });
	for (auto& [v, _] : buffer)
		std::cin >> v;

	// greedy
	for (int i = 1; i < N; ++i)
	{
		auto const& [pval, pcnt] = buffer[i - 1];
		auto& [val, cnt] = buffer[i];

		cnt = pcnt;

		// increase 
		int offset1 = 0;
		while ((val << offset1) < pval)
		{
			offset1++;
		}

		// decrease
		int offset2 = 0;
		while ((val << offset1) >= (pval << offset2))
		{
			offset2++;
		}
		cnt = std::max(0LL, cnt + offset1 - offset2 + 1);
	}

	/*
	// debug
	for (auto const& [_, cnt] : buffer)
	{
		std::cout << cnt << ' ';
	}
	*/

	// result
	// 모든 
	std::cout << std::accumulate(buffer.begin(), buffer.end(), 0LL, [](ll const acc, pii const& p) {
		return acc + p[1];
		});
}
