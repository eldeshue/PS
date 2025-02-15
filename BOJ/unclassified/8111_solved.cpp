
/*
	boj 8111, 0�� 1

	����� ���� ����. ycn ���� Ǯ����.
	ycn�� Ǯ�̸� �˷��༭ Ǯ����. �߻��� �� ���ذ� �ȵǾ��µ�...
	ycn�̴� dp�� Ǯ����, ���� �׷����� Ǯ��.

	10�� �ŵ������� ���� n���� ���� �������� 0�� �ǵ��� �ϴ� ������ ã��.
	�������� 0�̶� ���� �� ����� �ǹ���.
	���� �������� ����ص� �ʿ䰡 ����.
	��� ���� üũ�� ������, ����� ������ �������� �����ȴٴ� ���� ���ϸ�
	�� �� ������ �������� ���� ���� �ٽ� �湮�� �ʿ䰡 ����.
*/

#include <iostream>
#include <bitset>
#include <tuple>
#include <queue>
#include <string>

using gooNum = std::bitset<1000>;
using node = std::tuple<gooNum, int, int>; // goosaga number, remainder, digit

void printExceptZero(const gooNum& num) // ��� ��¿�, ��Ʈ���� ���� ���ӵ� 0��Ʈ�� ��������� ��.
{
	int idx = 99;
	while (num[idx] == 0) // 0�� ������
		idx--;
	while (idx >= 0) // ó������ 0�� �ƴ� ���� ���� �����
		std::cout << num[idx--];
	std::cout << '\n';
	return;
}

void bfs(int N)
{
	std::queue<node> Q;
	std::bitset<20000> visited(0); // �湮 ���� üũ ��Ʈ��
	gooNum nextNum;
	int nextRemain;

	if (N == 1)
	{
		std::cout << "1\n";
		return;
	}
	Q.push(std::make_tuple(gooNum(1), 1, 0));
	while (!Q.empty())
	{
		const gooNum& curNum = std::get<0>(Q.front());
		const int& curRemain = std::get<1>(Q.front());
		const int& curDigit = std::get<2>(Q.front());

		// depth limit
		if (curDigit == 100)
			break;
		// * 10
		nextNum = curNum << 1;
		nextRemain = (curRemain * 10) % N;
		if (nextRemain == 0) // ã�Ҵٸ�
		{
			printExceptZero(nextNum);
			return;
		}
		if (visited[nextRemain] == 0) // �̹湮�̸� �߰�
		{
			visited[nextRemain] = 1;
			Q.push(std::make_tuple(nextNum, nextRemain, curDigit + 1));
		}
		// * 10 + 1
		nextNum = curNum << 1;
		nextNum[0] = 1;
		nextRemain = (curRemain * 10 + 1) % N;
		if (nextRemain == 0)
		{
			printExceptZero(nextNum);
			return;
		}
		if (visited[nextRemain] == 0)
		{
			visited[nextRemain] = 1;
			Q.push(std::make_tuple(nextNum, nextRemain, curDigit + 1));
		}
		Q.pop();
	}
	// Ž�� ����, ycn�� ������ BRAK�� �߻��� �� ������ ���������� ����Ǿ� �ִµ�
	// �� �ȹٷ� Ǯ�⸸ �ߴٸ� �� �� ���� �޽�����.
	std::cout << "BRAK\n";
	return;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int testNum, n;
	std::cin >> testNum;
	for (int i = 0; i < testNum; ++i)
	{
		std::cin >> n;
		bfs(n);
	}
}