
/*
	
	boj 1024, ������ ��

	������ � �����ﰢ���� �غ��� �����ϴ� ���簢���� ������ ������ ����.

	���� L * (L - 1) / 2�� ����. -> � �����ﰢ���� ����
	N���� ������ ����, 
	N���� ũ�ٸ� ���� �Ǻ��� ����
	�⺻������ L��ŭ �ø��ų� L + 1��ŭ �ø� �� ����	

	L��ŭ �ø��� -> �ﰢ�� Ȯ�� ����, ������ ������ �������� ���̰� ���簢����.
	L + 1��ŭ �ø��� -> �ﰢ�� Ȯ��, �������� ���簢���� �ȵ�.

*/
#include <iostream>

int N, L;		// N : total sum, L : minimum length of the arr

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int start;
	std::cin >> N >> L;
	if ((L * (L - 1) / 2) > N)
	{
		std::cout << -1;
		return 0;
	}
	start = 0;
	N -= L * (L - 1) / 2;
	while (N > 0)
	{
		if (N % L == 0)
		{
			start = N / L;
			N = 0;
			break;
		}
		N -= L++;
	}
	if (L > 100 || N < 0)
	{
		std::cout << -1;
		return 0;
	}
	for (int i = 0; i < L; ++i)
	{
		std::cout << start + i << ' ';
	}
	return 0;
}