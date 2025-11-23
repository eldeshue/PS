/*
	BOJ 1493

	직육면체 길이 a, b, c라 하자
	그 길이는 순서대로라 할 때, 정육면체로 떠낼 수 있는 길이는 최대 a임.

	길이 a인 정육면체로 떠내고 나면 남은 부분은 크게 3개 덩어리로 분할됨

	1번
	b%a, a, c - (c%a)
	2번
	c%a, a, b - (b%a)
	3번
	b%a, c%a, a

	문제는 3번 조각을 어디에 붙여줘야 하는지가 문제임

	둘 중 더 큰 쪽에다 붙인다

	3 4 5

	====================================================

	가능한 큐브의 종류가 정해져 있음.

	큐브의 한 변의 길이는 2^i임.
	큐브의 길이가 2의 거듭제곱이라 붙이건 말건 상관이 없음.

	따라서, 주어진 직육면체를 8분할 하기만 하면 됨.
*/
#include <iostream>
#include <array>
#include <tuple>
#include <optional>

using ll = long long;
std::array<ll, 20> cubes;

void sort3(ll& a, ll& b, ll& c)
{
	if (a > b)
		std::swap(a, b);
	if (b > c)
		std::swap(b, c);
	if (a > b)
		std::swap(a, b);
}

ll div_cqr(ll pos, ll min, ll mid, ll max)
{
	ll result = 0;

	sort3(min, mid, max);
	if (min == 0)	// base case 1
		return 0;
	while ((1 << pos) > min || cubes[pos] == 0)
	{
		pos--;
		if (pos == -1)
		{
			return -1;	// base cae 2
		}
	}
	ll const len = (1 << pos);
	ll const cnt = (min / len) * (mid / len) * (max / len);
	ll ra = min % len;
	ll rb = mid % len;
	ll rc = max % len;
	ll da = min - ra;
	ll db = mid - rb;
	ll dc = max - rc;

	// split 8 rectangle
	ll temp = 0;
	if (cnt <= cubes[pos])
	{
		result += cnt;
		cubes[pos] -= cnt;
	}
	else
	{
		// optional first
		result += cubes[pos];
		ll const used_cnt = cubes[pos];
		cubes[pos] = 0;
		temp = div_cqr(pos, len, len, len * (cnt - used_cnt));
		if (temp == -1)
			return -1;
		result += temp;
	}
	temp = div_cqr(pos, ra, db, dc);
	if (temp == -1)
		return -1;
	result += temp;

	temp = div_cqr(pos, da, rb, dc);
	if (temp == -1)
		return -1;
	result += temp;

	temp = div_cqr(pos, da, db, rc);
	if (temp == -1)
		return -1;
	result += temp;

	temp = div_cqr(pos, ra, rb, dc);
	if (temp == -1)
		return -1;
	result += temp;

	temp = div_cqr(pos, ra, db, rc);
	if (temp == -1)
		return -1;
	result += temp;

	temp = div_cqr(pos, da, rb, rc);
	if (temp == -1)
		return -1;
	result += temp;

	temp = div_cqr(pos, ra, rb, rc);
	if (temp == -1)
		return -1;
	result += temp;

	return result;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::fill(cubes.begin(), cubes.end(), 0);

	// input
	ll a, b, c, N;
	std::cin >> a >> b >> c >> N;
	for (ll i = 0; i < N; ++i)
	{
		ll j, k;
		std::cin >> j >> k;
		cubes[j] = k;
	}

	// divide and conquer
	// sort
	std::cout << div_cqr(19, a, b, c);
}
