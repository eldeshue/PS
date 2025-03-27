
#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
	먼저 grid의 각 원소에 대하여 +-x를 하여 통일이 가능하려면
	grid의 모든 원소가 x로 나눈 나머지가 같아야 함.

	문제의 목적은 통일을 할 때, 증/감 횟수가 최소가 되어야 함.
	어떤 값 y에 대하여 증/감 횟수는 절대 편차(absolute deviation)이고,
	y에 따른 절대 편차의 총 합을 y에 대한 비용 함수라 한다.

	이러한 비용 함수는 아래로 볼록한 함수로, 그 최솟값은 중간값(median)에서 찾아짐이 증명이 되어있는데
		-> 나는 몰라서 평균으로 박다가 틀려서 검색해서 찾음
	중간값을 구해서 절대 편차의 총 합을 구하면 됨.

	그런데, 여기서 Quick-Select 알고리즘을 활용하면 정렬을 수행하지 않아도 중간값을 구할 수 있음.
	놀랍게도 Quick-Select 알고리즘은 거의 O(N), 매우 드물게 O(N log N)에 동작하기에 굉장히 빠름.
*/

#include <algorithm>
#include <numeric>

class Solution
{
private:
public:
	int minOperations(vector<vector<int>>& grid, int x) {
		int const N = grid.size();
		int const M = grid[0].size();
		int const Cnt = N * M;
		vector<int> buffer(Cnt, 0);

		// pre-processing, modulo check
		const int mod = grid[0][0] % x;
		for (int r = 0; r < N; ++r)
		{
			for (int c = 0; c < M; ++c)
			{
				if ((grid[r][c] % x) != mod)
				{
					return -1;
				}
				buffer[r * M + c] = grid[r][c] / x;
			}
		}

		// get median value of the buffer.
		// using IntroSelect algorithm, near O(N), worst O(N log N)
		nth_element(buffer.begin(), buffer.begin() + Cnt / 2, buffer.end());
		int const median = buffer[Cnt / 2];

		// get sum of absolute deviation
		// get minimum sum of absolute deviation by using median value
		return accumulate(buffer.begin(), buffer.end(), 0, [median](int const acc, int const n) { return abs(n - median) + acc; });
	}
};
