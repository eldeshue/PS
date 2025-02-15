/*
	row�� colum�� �����´�.
	colum�ϳ��� �ϳ��� bitset���� �ΰ� ~�������� ������Ų��
*/
#include <iostream>
#include <array>
#include <bitset>

using RAMP_COL = std::bitset<50>;
using TABLE = std::array<RAMP_COL, 50>;	// table[ colum ][ Row ];

// worst 2^50, TLE, failed.
int maxBrightRow(TABLE& t, const int MAX_COL, const int MAX_ROW, const int MAX_CNT, int colNum, int switchCnt)
{
	if (colNum == MAX_COL)
	{
		int cnt = 0;
		if (((MAX_CNT - switchCnt) & 1))
			return 0;
		for (int r = 0; r < MAX_ROW; ++r)
		{
			bool stat = true;
			for (int c = 0; c < MAX_COL; ++c)
			{
				stat = stat && t[c][r];
			}
			cnt += static_cast<int>(stat);
		}
		return cnt;
	}
	else
	{
		int result = maxBrightRow(t, MAX_COL, MAX_ROW, MAX_CNT, colNum + 1, switchCnt);
		t[colNum] = ~t[colNum];
		result = std::max(result,
			maxBrightRow(t, MAX_COL, MAX_ROW, MAX_CNT, colNum + 1, switchCnt + 1));
		t[colNum] = ~t[colNum];
		return result;
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	TABLE t;

	char c;
	int R, C, k;
	std::cin >> R >> C;
	for (int i = 0; i < R; ++i)
	{
		for (int j = 0; j < C; ++j)
		{
			std::cin >> c;
			t[j][i] = static_cast<bool>(c - 48);
		}
	}
	std::cin >> k;
	std::cout << maxBrightRow(t, C, R, k, 0, 0);
}
