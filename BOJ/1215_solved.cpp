
/*
	result = accumulate(1, n, 0, [k](ll const acc, ll const i){
		return acc + k % i; });

	�������� �䱸�ϴ� �ٴ� 1~n�� i�� ���Ͽ� k mod i�� �� ���� ���ϴ� ����

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

	// ����Ե� �ð� ���⵵�� sqrt(n) �̴�.
	// �� ������ ���� �����ϰ� �����Ǵ� ����� ������ sqrt(n)�� �Ǳ� ����
	// 
	while (i <= n)	// i from 1 to n, sum i * floor( k / i )
	{
		// q : ��, floor( k / i )
		ll q = k / i;
		// r : ������, ������ ��q�� �����ϴ� ������ ����
		ll r = k % i;
		// j : k�� i�� ���� ������ q�� ���� ������ ���� ������ ��ġ
		ll j = std::min(i + r / q, n);	// do not go beyond n

		// i * floor( k / i ) = i * q
		// q�� ���̰�, ��� i�� ���� ���� ���� ���ϸ� TLE��
		// ����, ��(q)�� ���� ���� ������ ���� �� ���� ����
		// q�� �����ϹǷ�, i�� ���� ���������� �տ� q�� ���Ѱ� ��
		result -= q * (i + j) * (j - i + 1) / 2;
		i = j + 1;	// ���� ������ ���� ��ġ�� �̵�
	}
	std::cout << result;
}