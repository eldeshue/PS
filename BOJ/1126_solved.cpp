
/*
BOJ 1126, ���� ž

������ �̸����� ��Ʈ�� ���� ��. ���� ž -> �� ž�� ������ ���ʿ���.

�� ž�� ���� ������ �ʿ䰡 ����. -> �߿��� ���� �� ž�� ���� ������.

cache[i�� ��ü][�� ž�� gap] = ���ݱ��� ������ �ʰ� ����� ��ü �� ��, �ִ밪

cache�� ���� A, ���簢���� ���̸� B

�׳� j�� �ش� ���� ������ ����

j + B[i] �� ���� ž�� �������� j�� ���̴� ����, �� �� ž �� ���� �ʿ��� ����

abs( j - B[i] )�� ���� ž�� ���� ���̸� j�� �ø��� ����, �� �� ž �� ū �ʿ� ����

A[i][j] = max(	
		A[ i-1 ][ j ],					// B[i]�� �����ų�
		A[ i-1 ][ j +  B[i]  ] ,		// B[i]�� �� ���� ž�� �װų�
		A[ i-1 ][ abs( j - B[i] ) ]		// B[i]�� �� ���� ž�� �װų�
			)
*/
#include <iostream>
#include <array>

using Cache = std::array<int, 500001>;
Cache c1, c2;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::fill(c1.begin(), c1.end(), -1);
	std::fill(c2.begin(), c2.end(), -1);
	c1[0] = 0;
	c2[0] = 0;
	Cache* pprevCache = &c1;
	Cache* pcurCache = &c2;

	int N, curVal;
	std::cin >> N;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> curVal;
		// tabulation
		for (int curGap = 0; curGap <= 500000 - curVal; ++curGap)
		{
			const int prevGap1 = curGap + curVal;	// ���� gap�� �� ũ��
			const int prevGap2 = std::abs(curGap - curVal);	// ���� gap�� �� �۴�
			(*pcurCache)[curGap] = (*pprevCache)[curGap];	// curVal�� ������ ���
			if ((*pprevCache)[prevGap1] != -1)
			{
				// �� ž�� ���̸� ������ ���
				(*pcurCache)[curGap] = std::max((*pcurCache)[curGap],
					(*pprevCache)[prevGap1] + curVal);
			}
			if ((*pprevCache)[prevGap2] != -1)
			{
				// �� ž�� ���̸� ������ ���
				(*pcurCache)[curGap] = std::max((*pcurCache)[curGap],
					(*pprevCache)[prevGap2] + curVal);
			}
		}
		std::swap(pprevCache, pcurCache);
	}
	if ((*pprevCache)[0] == 0)	// impossible, ���̰� 0���� ������ ���� ����
		std::cout << -1;
	else
		std::cout << (*pprevCache)[0] / 2;	// ������ ����� ���� ���̹Ƿ�, 2�� ����
}