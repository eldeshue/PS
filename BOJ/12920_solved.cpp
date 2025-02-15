
/*
	boj 12920, ����� �賶 2

	������ �߻��� ���� ����. ���� ���� �� ���� �ӿ��� � �����ΰ�?

	���������� ������ 01 �賶 ������ �ٸ���, �� ��ü�� ���� ���� ������ �־�����.
	�� �������� �����ߴ� ���� ���η� dp�� �����ϴ� ���� �Ұ����ϴ�.

	���� Ǯ���� �߻��� �ٷ� �� ������ �����ؼ� ������ 01 �賶���� ȯ���ϴ� ��.
	������ ��ü�� ���� �����ϴ� ������ �߻��ϴ� ������ �ٷ� �ټ��� �ߺ��� �߻��Ͽ� �ð� ���⵵�� 
	�����ϴ� ��.
	�̷��� �ߺ��� �����ϱ� ���ؼ� n���� ��ü�� ���� ��ǰ���� �����.
	��� ��ü ������ ���� �߿����� ������, �߿��� ���� �� ���� ���õǴ����� �����̴�.
	�׷��⿡ ��ü ������ ���ؼ� Ž���� ������ �ʿ䰡 ����. �߿��� ���� n���� ��ü�� ���ؼ� �߻��ϴ�
	������ ���ɼ��̴�.

	�̷��� ������ �����ϱ� ���ؼ� ��ü�� ���� n�� 2�� ���� �����Ͽ� ���� ��ǰ�� ������. 

*/

/*
#include <iostream>
#include <algorithm>
#include <vector>
#include <memory.h>

using item = std::pair<int, int>;
std::vector<item> items;
int cache[10001];

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(cache, -1, sizeof(cache));

	int N, MW, c, v, n;
	std::cin >> N >> MW;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> c >> v >> n;
		// ��ü�� ���� ������ �����Ͽ� 01�賶���� ȯ���ϴ� ���.
		// ��ü�� ������ 2������ ������ �����Ͽ� �̵��� ���� �ϳ��� ��ü�� ���
		// �̸� ���ؼ� ������ ������ ��ü�� ���� �����Ͽ� �߻��ϴ� �ߺ��� ������ �� ����.
		// ���� k�� 2���� �������� ����
		for (int b = 1; n > 0; b <<= 1)
		{
			const int ix = std::min(b, n);
			items.push_back(std::make_pair(c * ix, v * ix));
			n -= ix;
		}
	}
	cache[0] = 0;
	for (int inum = 0; inum < items.size(); ++inum)
	{
		const int& cost = items[inum].first;
		const int& val = items[inum].second;
		for (int cur_cost = MW; cur_cost >= cost; --cur_cost)
		{
			if (cache[cur_cost - cost] != -1)
			{
				cache[cur_cost] 
					= std::max(cache[cur_cost], cache[cur_cost - cost] + val);
			}
		}
	}
	int result = 0;
	for (int i = 0; i <= MW; ++i)
	{
		result = std::max(result, cache[i]);
	}
	std::cout << result;
}
*/