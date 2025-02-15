
#include <iostream>
#include <vector>

/*
	Kadane's algorithm

	���� Ǯ�̴� two pointer���� ������. 
	�� ���� �����͸� substring�� ���۰� ���� ����Ŵ.

	�������� ����� ���� ������ �����͸� ������Ŵ.
	�������� ������ �Ǵ� ����, �� �����͸� ���� ��ġ �������� ����.

	�� ���ݱ��� ���� �������� �ִ� �����տ� ������ �ȵǸ�, �̸� ������ ��.
	�������� ������ �Ǵ� ���ȿ��� �����ϰ�, �׷��� ������ ������.
	
	�������� �����ϴ� ���� �ִ���, ������ �ִ� �������� �Ϻΰ� �� ���ɼ��� ����.
	������, �������� ������ �Ǵ� ����, ������ �������� �����ϴ� ���� ���ذ� ��.

	���� �̷��� �� �����Ϳ��� ������ �������״µ�, 
	����� Kadane's algorithm�̶�� ������ ��ũ���̾���. dp�� ����ȭ.
*/

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, num, maxSum = -2e9, curSum = 0;
	std::cin >> N;
	for (int i = 0; i < N; ++i)				// O(N)
	{
		std::cin >> num;
		curSum += num;						// ���� ����
		maxSum = std::max(maxSum, curSum);	// �ִ� ������Ʈ
		if (curSum < 0)						// ������ ���� ���� ����.
			curSum = 0;
	}
	std::cout << maxSum;
}