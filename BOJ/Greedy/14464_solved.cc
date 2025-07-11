/*
	BOJ 14464

	닭T가 소의 범위 A,B 사이에 들어야 한다.
	소와 닭은 0대1 매칭으로 이루어진다.
	최대한의 매칭을 구해야 한다. -> 이분 매칭

	===========================================
	굳이 이분 매칭을 안해도 될 것으로 보인다.
	일단 문제의 테마가 그리디 이기도 하고,

	내 생각은 닭의 입장에서 여러 소의 범위에 들 수 있다고 생각이 된다.
	그렇다면, 가장 적은 닭이 매칭된 소들 먼저 비우면 최대한의 매칭을 이룰 수 있지 않을까????

	=========================================
	0)
	4 5
	0
	5
	3
	7
	8
	0 6
	1 5
	2 7
	-1 46
	3 5

	0 -> 1 6
	5 -> 3 7
	3 -> 4 5 or 2 5
	7 -> 0 46

	0 4 6 8 9
	(1 5) (4 5) (1 6) (3 7) (0 46)

	==========================================
	< solution, sweeping >

	0) pre-processing
	먼저 수직선을 정렬한다.

	1) priority queue
	수평 선분을 저장하는 우선순위 큐를 준비한다.
	수평 선분의 r값의 min heap이다.

	2) sweeping
	수직 성분 좌표를 순회하면서,
	2.1) 현재 수직선보다 r값이 작은 선분, 즉 교차하지 않는 선분을 모조리 pop.
	2.2) 현재 수직선과 교차하는 선분을 찾으면 matching_count를 증가시키고 매칭한 선분을 pop.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>

using Line = std::pair<int, int>;

struct comp {
	bool operator()(Line const& l0, Line const& l2)
	{
		// check end first
		if (l0.second == l2.second)
		{
			return l0.first > l2.first;
		}
		return l0.second > l2.second;
	}
};

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int C, N;
	std::cin >> C >> N;
	std::vector<int> vertical(C);
	for (auto& t : vertical)
		std::cin >> t;
	std::deque<Line> horizontal(N);
	for (auto& l : horizontal)
		std::cin >> l.first >> l.second;
	std::sort(vertical.begin(), vertical.end());
	std::sort(horizontal.begin(), horizontal.end());

	// sweep
	int result = -1;
	std::priority_queue<Line, std::vector<Line>, comp> pq;
	for (auto const t : vertical)
	{
		// push till cross
		while (!horizontal.empty() && horizontal.front().first <= t)
		{
			pq.push(horizontal.front());
			horizontal.pop_front();
		}
		// pop un-crossed
		while (!pq.empty() && pq.top().second < t)
		{
			pq.pop();
		}
		// get crosssed
		if (!pq.empty() && pq.top().first <= t)
		{
			result++;
			pq.pop();
		}
	}

	// print
	std::cout << result;
}
