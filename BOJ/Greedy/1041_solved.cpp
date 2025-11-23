/*
	BOJ 1041

	greedy

	노출되는 면을 3종으로 나눔

	3개 면이 노출되는 블럭
	2개 면이 노출되는 블럭
	1개 면이 노출되는 블럭

	각 경우에 대해서 최솟값을 구한 다음, 개수를 count해서 총 합을 구한다.
	밑에 깔리는 한 면이 노출되지 않으므로, 이 부분 주의할것
*/
#include <iostream>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	long long N;
	int a, b, c, d, e, f;
	std::cin >> N >> a >> b >> c >> d >> e >> f;

	// 예외처리
	if (N == 1)
	{
		int sum = a + b + c + d + e + f;
		int max = std::max(std::max(std::max(a, b), std::max(c, d)), std::max(e, f));
		std::cout << sum - max;
		return 0;
	}

	// min 1
	long long const min1 = std::min(std::min(std::min(a, b), std::min(c, d)), std::min(e, f));

	// min 2
	int ab = a + b;
	int ad = a + d;
	int ae = a + e;
	int ac = a + c;

	int de = d + e;
	int ce = c + e;
	int bc = b + c;
	int bd = b + d;

	int bf = b + f;
	int cf = c + f;
	int df = d + f;
	int ef = e + f;

	long long const min2 = std::min(std::min(
		std::min(std::min(ab, ad), std::min(ae, ac)),
		std::min(std::min(de, ce), std::min(bc, bd))
	), std::min(std::min(bf, cf), std::min(df, ef)));

	// min 3
	int abc = a + b + c;
	int ace = a + c + e;
	int aed = a + e + d;
	int adb = a + d + b;

	int fbc = f + b + c;
	int fce = f + c + e;
	int fed = f + e + d;
	int fdb = f + d + b;

	long long const min3 = std::min(
		std::min(std::min(abc, ace), std::min(aed, adb)),
		std::min(std::min(fbc, fce), std::min(fed, fdb))
	);

	// greedy
	// 5 faces...
	std::cout <<
		4 * min3
		+ 4 * ((N - 2) + (N - 1)) * min2
		+ ((N - 2) + 4 * (N - 1)) * (N - 2) * min1;
}
