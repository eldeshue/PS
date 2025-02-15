
/*
	result = accumulate(1, n, 0, [k](ll const acc, ll const i){
		return acc + k % i; });

	문제에서 요구하는 바는 1~n인 i에 대하여 k mod i의 총 합을 구하는 문제

	k mod i = k - i * floor(k / i)

	result = n * k - sum(1, k - 1, 0, i * floor(k / i) )

*/
#include <iostream>

using ll = long long;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	ll n, k, result = 0;
	std::cin >> n >> k;
	if (n >= k)	// k < i <= n, k % i == k
	{
		result += k * (n - k);
		// if k == i is zero, so skip
		n = k - 1;
	}
	// if i < k
	result += n * k;
	ll i = 1;

	// 놀랍게도 시간 복잡도가 sqrt(n) 이다.
	// 그 이유는 몫이 일정하게 유지되는 블록의 개수가 sqrt(n)이 되기 때문
	// 
	while (i <= n)	// i from 1 to n, sum i * floor( k / i )
	{
		// q : 몫, floor( k / i )
		ll q = k / i;
		// r : 나머지, 동일한 몫q을 유지하는 영역의 길이
		ll r = k % i;
		// j : k를 i로 나눈 몫으로 q를 갖는 영역의 가장 마지막 위치
		ll j = std::min(i + r / q, n);	// do not go beyond n

		// i * floor( k / i ) = i * q
		// q가 몫이고, 모든 i에 따른 위의 값을 구하면 TLE임
		// 따라서, 몫(q)의 값이 같은 영역의 값을 한 번에 구함
		// q가 일정하므로, i에 대한 등차수열의 합에 q를 곱한게 됨
		result -= q * (i + j) * (j - i + 1) / 2;
		i = j + 1;	// 다음 영역의 시작 위치로 이동
	}
	std::cout << result;
}