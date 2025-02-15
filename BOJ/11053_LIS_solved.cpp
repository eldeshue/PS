
#include <iostream>
#include <algorithm>
#include <vector>

int N;
std::vector<int> buffer;
std::vector<int> cache;			// cache[length] = final value of the LIS

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> N;
	buffer.resize(N);
	for (int i = 0; i < N; ++i)
	{
		std::cin >> buffer[i];
	}

	// LIS using upper bound
	cache.push_back(buffer[0]); // �ʱⰪ
	for (int i = 1; i < N; ++i)
	{
		if (buffer[i] > *cache.rbegin()) // append
		{
			cache.push_back(buffer[i]); // ���ݱ��� ã�� LIS�� ��, ���� �� ���� final������ ũ��.
										// �� ���ο� LIS�� ������ �κ���.
		}
		else // ������ LIS���� ����, ���� ������ LIS�߿��� final value�� ������.
		{
			// update
			// find position to update by using lower_bound
			// lower_bound�Լ��� 2��Ž���Ͽ� LIS�� final value�� �����Ѵ�.
			// lower_bound�Լ��� ���ڷ� ���޵� �� �̻��� ���� ó������ �����ϴ� ��ġ�� index�� ��ȯ��
			*(std::lower_bound(cache.begin(), cache.end(), buffer[i])) = buffer[i];
		}
	}
	std::cout << cache.size(); // ���� �� LIS�� ���̸� ��ȯ��.
}