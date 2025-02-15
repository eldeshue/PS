
#include <iostream>
#include <memory.h>
#include <string>

int N;
int num[10];	// little endian

// �ڸ����� Ŀ���� ������ ���鼭, �� �ڸ������� �ִ�� ���� �� �ִ� ������ Ȯ���ؼ�... 
bool BT(int& maxRank, int cnt)
{
	if (cnt == N)
	{
		return true;
	}
	else
	{
		num[0]++;
		// carry
		for (int rank = 0; rank <= maxRank; ++rank)
		{
			if (rank == maxRank)
			{
				if (num[rank] > 9)	// carry �߻� ����, �߻��ϸ� expand
				{
					if (maxRank == 9)	// expand �Ұ��� ����
					{
						return false;
					}
					else
					{
						maxRank++;
						num[maxRank] = maxRank;
						num[rank] = rank;
						break;
					}
				}
				else
				{
					break;
				}
			}
			else // maxRank�� �ƴ�. simple carry
			{
				if (num[rank] == num[rank + 1])	// carry �߻� ����
				{
					num[rank] = rank;
					num[rank + 1]++;
				}
				else
				{
					break;
				}
			}
		}
	}

	return BT(maxRank, cnt + 1);
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(num, 0, sizeof(num));

	std::cin >> N;

	int maxRank = 0;
	if (BT(maxRank, 0))
	{
		for (int i = maxRank; i >=0; --i)
		{
			std::cout << num[i];
		}
	}
	else
	{
		std::cout << -1;
	}
}