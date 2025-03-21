
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using line = std::pair<int, int>;

// start, ascending order
bool cmp_line_sort(const line& l1, const line& l2)
{
	if (l1.first == l2.first)
		return (l1.second < l2.second);
	return (l1.first < l2.first);
}

struct cmp_line_pq	// minimum heap, second
{
	bool operator()(const line& l1, const line& l2)
	{
		if (l1.second == l2.second)
			return (l1.first > l2.first);
		return (l1.second > l2.second);
	}
};

std::vector<line> lines;
std::priority_queue<line, std::vector<line>, cmp_line_pq> PQ;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	std::cin >> N;
	lines.resize(N);
	for (int i = 0; i < N; ++i)
	{
		std::cin >> lines[i].first >> lines[i].second;
	}
	std::sort(lines.begin(), lines.end(), cmp_line_sort);
	// sweeping
	int max_overlap = 0, cur_overlap = 0;
	for (int i = 0; i < N; ++i)
	{
		if (!PQ.empty() && PQ.top().second <= lines[i].first)
		{
			PQ.pop();
			cur_overlap--;
		}
		PQ.push(lines[i]);
		cur_overlap++;
		max_overlap = std::max(max_overlap, cur_overlap);
	}
	std::cout << max_overlap;
}
