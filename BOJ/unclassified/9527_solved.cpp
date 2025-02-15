
/*
	g(k)를 2^k이하의 모든 수의 비트 개수라 하자.
		g(k) = 2 * g(k - 1) + 2 ^ (k - 1)
			= k * 2 ^ (k - 1)

	F(n)을 n이하의 모든 수의 비트 개수라 하자.
	index of bit, i in range from 0 to 63에 대하여
	n[i]가 1인 경우 다음을 계산하여 누적.

	(msb에서부터 세어 온 비트들의 개수) * (해당 비트들이 중복 등장하는 횟수)
		+ (해당 위치 이하의 모든 1 비트 누적 개수)
	=>
	prevBitCnt * (1 << i) + g(i)
*/
#include <iostream>
#include <bitset>

using ull = unsigned long long;
using Bits = std::bitset<64>;

// F(n)에 대하여 n == 2 ^ k인 경우에 대한 특별해
// g(k)를 이용하여 F(n)을 계산함.
inline ull g(ull k)
{
	if (k == 0) return 0;
	return k * (1ULL << (k - 1));
}

ull F(const Bits &b)
{
	ull totalCnt = b.count();
	ull prevBitCnt = 0;

	for (long long i = 63; i >= 0; --i)
	{
		if (b[i])
		{
			totalCnt += prevBitCnt * (1ULL << i) + g(i);
			prevBitCnt++;
		}
	}
	return totalCnt;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	ull A, B;	// A <= B
	std::cin >> A >> B;
	std::cout << F(B) - F(A) + Bits(A).count();
}