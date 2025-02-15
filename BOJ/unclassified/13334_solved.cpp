// sweeping 알고리즘 응용
// priority queue를 사용하여 현재 sweeping하는 구간에서
// 해당 구간에 포함된 개체들을 표현함.
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using line = std::pair<int, int>;
std::vector<line> lines;

bool cmp_line_vec(const line& a1, const line& a2)
{
	if (a1.second == a2.second)
	{
		return (a1.first < a2.first);
	}
	return (a1.second < a2.second);
}

struct cmp_line_pq	// min heap
{
	bool operator()(const line& a1, const line& a2)
	{
		return (a1.first > a2.first);
	}
};

// priority queue that save included lines, minimum heap
std::priority_queue<line, std::vector<line>, cmp_line_pq> PQ;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int n, d;
	std::cin >> n;
	lines.resize(n);
	for (int i = 0; i < n; ++i)
	{
		std::cin >> lines[i].first >> lines[i].second;
		if (lines[i].first > lines[i].second)
			std::swap(lines[i].first, lines[i].second);
	}
	std::cin >> d;
	std::sort(lines.begin(), lines.end(), cmp_line_vec);
	// sweeping
	int cur_val = 0, max_val = 0;
	// set initial state
	for (int idx = 0; idx < n; ++idx)
	{
		// too long to accept
		if (lines[idx].second - lines[idx].first > d)
		{
			continue;	// ignore;
		}
		// pop and push
		while (!PQ.empty() && lines[idx].second - PQ.top().first > d)
		{
			cur_val--;
			PQ.pop();
		}
		PQ.push(lines[idx]);
		cur_val++;
		max_val = std::max(max_val, cur_val);
	}
	std::cout << max_val;
}
