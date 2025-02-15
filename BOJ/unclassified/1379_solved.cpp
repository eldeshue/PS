
/*

	sweeping 2회... 그다지 스마트하진 않네요...

*/
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <tuple>
#include <memory.h>

using lect = std::tuple<int, int, int>;

bool cmp_ascend(const lect& l1, const lect& l2)
{
		if (std::get<1>(l1) == std::get<1>(l2))
		{
			return (std::get<2>(l1) < std::get<2>(l2));
		}
		return (std::get<1>(l1) < std::get<1>(l2));
}

int N;
std::vector<lect> lectures;

struct cmp_min_heap
{
	bool operator()(const int& lidx1, const int& lidx2)
	{
		const int& l1_start = std::get<1>(lectures[lidx1]);
		const int& l1_end = std::get<2>(lectures[lidx1]);
		const int& l2_start = std::get<1>(lectures[lidx2]);
		const int& l2_end = std::get<2>(lectures[lidx2]);
		if (l1_end == l2_end)
		{
			return (l1_start > l2_start);
		}
		return (l1_end > l2_end);
	}
};

std::priority_queue<int, std::vector<int>, cmp_min_heap> sweep_pq;

bool is_overlap(int start, int end)
{
	const int& top_s = std::get<1>(lectures[sweep_pq.top()]);
	const int& top_e = std::get<2>(lectures[sweep_pq.top()]);
	return (start < top_e && top_s < end);
}

int room[100001];
std::queue<int> empty_room;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(room, 0, sizeof(room));

	int num, start, end;
	std::cin >> N;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> num >> start >> end;
		lectures.push_back(std::make_tuple(num, start, end));
	}
	std::sort(lectures.begin(), lectures.end(), cmp_ascend);
	int result = 0, cur_lect_cnt = 0;
	for (int i = 0; i < lectures.size(); ++i)
	{
		const int& cur_s = std::get<1>(lectures[i]);
		const int& cur_e = std::get<2>(lectures[i]);
		while (!sweep_pq.empty() && !is_overlap(cur_s, cur_e))	// flush
		{
			sweep_pq.pop();
			cur_lect_cnt--;
		}
		// push
		sweep_pq.push(i);
		cur_lect_cnt++;
		result = std::max(result, cur_lect_cnt);
	}
	// find room number
	for (int i = 1; i <= result; ++i)
	{
		empty_room.push(i);
	}
	// sweep again
	while (!sweep_pq.empty())
		sweep_pq.pop();
	for (int i = 0; i < lectures.size(); ++i)
	{
		const int& cur_s = std::get<1>(lectures[i]);
		const int& cur_e = std::get<2>(lectures[i]);
		while (!sweep_pq.empty() && !is_overlap(cur_s, cur_e))	// flush
		{
			empty_room.push(room[std::get<0>(lectures[sweep_pq.top()])]);
			sweep_pq.pop();
		}
		// push
		sweep_pq.push(i);
		room[std::get<0>(lectures[i])] = empty_room.front();
		empty_room.pop();
	}
	// result
	std::cout << result << '\n';
	for (int i = 1; i <= N; ++i)
	{
		std::cout << room[i] << '\n';
	}
}