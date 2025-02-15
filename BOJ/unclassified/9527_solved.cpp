
/*
	g(k)�� 2^k������ ��� ���� ��Ʈ ������ ����.
		g(k) = 2 * g(k - 1) + 2 ^ (k - 1)
			= k * 2 ^ (k - 1)

	F(n)�� n������ ��� ���� ��Ʈ ������ ����.
	index of bit, i in range from 0 to 63�� ���Ͽ�
	n[i]�� 1�� ��� ������ ����Ͽ� ����.

	(msb�������� ���� �� ��Ʈ���� ����) * (�ش� ��Ʈ���� �ߺ� �����ϴ� Ƚ��)
		+ (�ش� ��ġ ������ ��� 1 ��Ʈ ���� ����)
	=>
	prevBitCnt * (1 << i) + g(i)
*/
#include <iostream>
#include <bitset>

using ull = unsigned long long;
using Bits = std::bitset<64>;

// F(n)�� ���Ͽ� n == 2 ^ k�� ��쿡 ���� Ư����
// g(k)�� �̿��Ͽ� F(n)�� �����.
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