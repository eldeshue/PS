
#include <iostream>
#include <vector>

using namespace std;
/*
	한 걸음에 방향을 바꾸고, 두 걸음에 보폭을 넓힌다.
		-> 시뮬레이션 풀이 가능.
		-> 중복이 많을 것으로 예상됨.
		-> N을 맵의 넓이라 하면, 최악의 경우 O(4N).

	시작점에서의 좌표를 바탕으로 순서를 얻을 수 있지 않을까?
	운행 패턴은 이미 정해져 있으므로, 그 상대적인 위치 정보만 얻으면
	도달 순서를 계산할 수 있음이다.
		-> 정렬이 필요함.
		-> O(N log N)이 될 것.
*/
#pragma GCC optimize("03")
#pragma GCC target("avx")
#pragma GCC target("-fsplit-loops")
class Solution
{
private:
	static constexpr int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

public:
	// solution method
	vector<vector<int>> spiralMatrixIII(int rows, int cols, int rStart, int cStart)
	{
		vector<vector<int>> result;

		int step = 1, d = 0, curRow = rStart, curCol = cStart;
		while (result.size() < rows * cols)
		{
			for (int i = 0; i < 2; ++i)
			{
				for (int j = 0; j < step; ++j)
				{
					if (0 <= curRow && curRow < rows && 0 <= curCol && curCol < cols) // in range
					{
						result.push_back({curRow, curCol});
					}
					curRow += dir[d][0];
					curCol += dir[d][1];
				}
				d = (d + 1) % 4; // change dir
			}
			step++;
		}
		return result;
	}
};
auto _ = []()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	return 0;
}();
//

// test
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;
}
