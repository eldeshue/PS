
/*
	이 문제는 N C K 를 계산하면 되는 단순하다면 단순한 문제이다.

	그러나... N,K는 4e7이고 1e9+7로 나눈 나머지를 구해야 한다.

	나눗셈에 대한 나머지 연산을 어떻게 수행하지???? 나눗셈에 대한 mod의 분배법칙, 결합법칙은 유효하지 않다.

	-> 페르마의 소정리를 도입하여 나눗셈에 나머지 연산을 적용한다.

	B^(P - 1) = 1(mod p) -> 페르마의 소정리

	B * B^(P - 2) = 1(mod P)

	B^(P - 2) = B^(-1) mod P

	mod 연산은 곱셈에 대해서는 결합이 가능하므로,

	AB(-1) mod P = A B^(P - 2) mod P = (A mod P) * ( B^(P - 2) mod P )

	가 된다. 따라서, A를 B로 나누는 나눗셈에 대한 나머지 연산을 곱셈에 대한 나머지 연산으로 바꾸는 데에 성공했다.

	따라서 N C K = N (N - 1) ... (N - K + 1) / {K (K - 1) ... 1} = N N - 1 .. N - K + 1 { K K - 1 ... * 1 } ^ (P - 2)

	A = N * (N - 1) * ... * (N - K + 1)
	B = K!

	여기서 N, K이 40M, P가 1e9+7 이므로, 매우매우 큰 수의 거듭제곱이 필요하다. 이 매우 큰 수의 거듭 제곱을 divide & conquer로 풀어준다.

	===================================

	문제 자체가 그냥 수학의 망치라서, 알면 풀것이고, 모르면 못푸는 그런 류의 문제이다.
 */

#include <iostream>

using ull = unsigned long long;
constexpr ull const DIV = 1e9 + 7;
ull temp;

ull PowAndMod(ull const base, ull const pow)
{
	if (pow == 0)
		return 1;
	temp = PowAndMod(base, pow / 2);	// divide and conquer
	temp = (temp * temp) % DIV;
	if (pow & 1)
		temp = (temp * base) % DIV;
	return temp;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	ull N, K;
	std::cin >> N >> K;

	// solve
	ull const A = [&]() {
		ull result = 1;
		for (int i = N; i >= (N - K + 1); --i)
			result = (result * i) % DIV;
		return result;
		}();
	ull const B = [&]() {
		ull result = 1;
		for (int i = 1; i <= K; ++i)
			result = (result * i) % DIV;
		return result;
		}();

	// by perma's little theorem, N C K can be converted to...
	ull const result = (A * (PowAndMod(B, DIV - 2) % DIV)) % DIV;

	std::cout << result;
}
