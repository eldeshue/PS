/*
	BOJ 2494

	단순 dp였던 13392번에 역추적을 가하여 최적의 선택 자체를 구하는 문제.

	===============================================

	왼쪽으로 돌리면(increase) 그 위의 숫자는 다 함께 회전
	오른쪽으로 돌리는(decrease) 것은 전파되지 않음

	가장 적은 움직임으로 목표 숫자에 도달하기

	===========================================

	특정 위치에서 왼쪽으로 돌리면 side effect가 발생함.

	일단 회전 순서는 의미가 없음. 순서는 바꿔도 됨.

	============================================

	각 층에서 할 수 있는 행동은 둘 중 하나임.
	왼쪽으로 돌리기 혹은 오른 쪽으로 돌리기.

	왼쪽으로 돌리면 그 다음 디스크를 돌릴 때, 왼쪽으로 돌린 것 만큼 고려해줘야 함.
	즉, 왼쪽으로 돌리면 그 결과가 다음에 영향을 미친다. 따라서 상황이 분리가 안된다.

	어떻게 optimal에 도달할 수 있음을 보장할 수 있을까? invariant가 뭘까?

	---------------------------------------------

	아래에서 위로 올라가며 진행하는게 맞음.

	위에서 아래로는 영향을 미치지만, 아래에서 위로는 영향을 미치지 않음.
	즉, 최적 부분구조가 아래에서 위로는 성립하는 것임.

	최적 부분 구조를 뭐로 계산하지? 좌회전수? 총회전수?
	일단 총회전수인 것 같기는 한데,
	좌회전수를 극한으로 땡겨서 위로 올라갈수록 병합의 이득을 올려야 하는가?

	위에서 무엇을 선택해도, 일단 해당 디스크를 최소로 돌려서 결과를 내줘야 함.

	==============================

	dp면 dp답게 상태를 정의해서 점화식으로 풀었어야 하는데, 기초를 잊었다.

	이 문제의 상태는

	디스크의 번호와
	해당 디스크와 그 이하의 누적 회전 수(를 10으로 나눈 나머지)가 몇이냐

	저장할 값은 최소 맞춤 비용임(해당 경우에 따른 좌/우 회전 횟수도 저장하면 좋음)
*/
#include <iostream>
#include <string>
#include <vector>
#include <numeric>

int cal_lrot(int cur, int goal) {
	if (cur > goal)
		goal += 10;
	return goal - cur;
}

int cal_rrot(int cur, int goal) {
	if (cur < goal)
		cur += 10;
	return cur - goal;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	int N;
	std::cin >> N;
	std::string cur_stat, goal_stat;
	std::cin >> cur_stat >> goal_stat;

	// character to integer
	for (int i = 0; i < N; ++i) {
		cur_stat[i] -= '0';
		goal_stat[i] -= '0';
	}

	// disk 번호, 해당 디스크에 도달하기까지 누적 회전 횟수 = 총 최소 회전 횟수
	std::vector<std::vector<int>> cache(N, std::vector<int>(10, 2e9));

	// back track

	// dp, tabulation, total 
	// base case
	for (int l = 0; l < 10; ++l)
	{
		int start = (cur_stat[N - 1] + l) % 10;
		cache[N - 1][l] = std::min(
			cal_lrot(start, goal_stat[N - 1]),
			cal_rrot(start, goal_stat[N - 1])
		);
	}
	for (int d = N - 2; d >= 0; --d)
	{
		// prev left count0
		for (int l = 0; l < 10; ++l)
		{
			int start = (cur_stat[d] + l) % 10;
			// left 
			{
				int left_move_cnt = cal_lrot(start, goal_stat[d]);
				int next_l = (l + left_move_cnt) % 10;
				cache[d][l] =
					std::min(cache[d][l], cache[d + 1][next_l] + left_move_cnt);
			}

			// right
			{
				int right_move_cnt = cal_rrot(start, goal_stat[d]);
				int next_l = l;
				cache[d][l] =
					std::min(cache[d][l], cache[d + 1][l] + right_move_cnt);
			}

		}
	}

	// print
	std::cout << cache[0][0] << '\n';

	// back track
	// from 0, 0 to N-1
	int prev_l = 0;
	for (int d = 0; d < N; ++d)
	{
		// cur start
		int start = (cur_stat[d] + prev_l) % 10;

		// current move
		int l_cnt = cal_lrot(start, goal_stat[d]);
		int r_cnt = cal_rrot(start, goal_stat[d]);

		// get total
		int l_total = l_cnt;
		int r_total = r_cnt;
		if (d < N - 1)
		{
			l_total += cache[d + 1][(l_cnt + prev_l) % 10];
			r_total += cache[d + 1][prev_l];
		}

		// compare, pick left or right
		// update prev_l
		// print decision
		if (l_total < r_total)
		{
			// left wins
			std::cout << d + 1 << ' ' << l_cnt << '\n';
			prev_l = (prev_l + l_cnt) % 10;
		}
		else
		{
			// right wins
			std::cout << d + 1 << ' ' << -r_cnt << '\n';
			// keep the prev_l
		}
	}
}
