
/*
	�߻��� ��ȯ�� �����̴� �ǰ� ���� ����.

	���� B�� K��° ���Ҷ� ����
	��Ŀ��� �ش� ���Һ��� ���� ������ ������ K - 1�� ������ �ǹ���.
	�� �κ��� ������ catch�ϸ� �̺�Ž������ �̾ ������ �� ����.

	�׷���..... ���� ������ ����� ���� �ߴµ�,
	����� �����ϴ� ������ ������ �ذ��Ϸ� �߱� ����

	����̶�� ��� ���Ͽ�, �� ������ ��ġ�� �������� ����,
	����� �����ϴ� ����, �� ��ü�� ������ �ʿ䰡 ����.

	�ٸ�, �ش� ������ ��� key idea�� �̺� Ž������ �˰� Ǯ� ��������
	��� �̺�Ž���̶�� Ű���带 �����ٸ� ����� ����� ������ ����.

	��� 1�� �� �����򰡵� ����� ���.
*/
#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>

using ll = long long;

bool isLessGreaterThanK(const ll N, const ll K, const ll num)
{
	ll cnt = 0;
	// ����� �� row�� ���ؼ� num���� ���� ������ ������ collect
	// �� row���� num ���� ���� ������ ������ �� �� �ϳ���.
	// �ش� row�� ��� ������ num���� ���� ���, N��
	// ex ) N = 5, row = 2, num = 20�� ��� -> min(5, 10) = 5�� (2, 4, 6, 8, 10)
	// �� ���� ���� row�� ������ num�� ������ ���� �� ��ŭ num���� ����
	// ex ) N = 11, row = 9, num = 20�� ��� -> 9, 18�� �� ��
	for (ll i = 1; i <= N; ++i)	
	{
		cnt += std::min(N, num / i);
	}
	return cnt >= K;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	ll N, K;
	std::cin >> N >> K;
	// lower bound
	auto isOk = std::bind(isLessGreaterThanK, N, K, std::placeholders::_1);
	ll left = 1, right = N * N + 1;	// B[K] �� K���� �׻� �۱⿡ K�� �ᵵ ��.
	while (left < right)
	{
		ll mid = (left + right) >> 1;
		if (isOk(mid))
			right = mid;
		else
			left = mid + 1;
	}
	std::cout << left;
}