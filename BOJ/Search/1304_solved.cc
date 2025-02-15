
#include <iostream>
#include <vector>

using SCC = std::pair<int, int>;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, M;
	std::cin >> N >> M;
	std::vector<int> graph(N, 2e9);
	for (int i = 0; i < M; ++i)
	{
		int s, e;
		std::cin >> s >> e; // input city 1 ~ N, -> 0 ~ N-1
		if (s > e)
			graph[s - 1] = std::min(graph[s - 1], e - 1);
	}
	std::vector<SCC> scc;
	int right = N - 1, left = N - 1;
	// building scc, lots of error occured, O(2 * N)
	while (left >= 0)
	{
		if (graph[left] == 2e9)
		{
			// push_back
			scc.push_back(std::make_pair(left, right));
			// move next
			right = --left;
		}
		else
		{
			// graph[left] is next position, left is prev position
			int farestLeft = graph[left];
			for (int pos = left - 1; pos > graph[left]; --pos) // check gap between prev and next pos
			{
				farestLeft = std::min(farestLeft, graph[pos]);
			}
			left = farestLeft;
		}
	}
	int result = 1;
	for (int len = 1; len < N; ++len)
	{
		bool isSplitable = true;
		int curCutNode = N - len, cnt = 0;
		for (int i = 0; i < scc.size(); ++i)
		{
			if (scc[i].first < curCutNode && curCutNode <= scc[i].second) // split fail
			{
				isSplitable = false;
				break;
			}
			else if (scc[i].first == curCutNode) // found
			{
				curCutNode -= len;
				cnt++;
			}
		}
		if (isSplitable && curCutNode == -len && N / len == cnt && N % len == 0)
		{
			result = cnt;
			break;
		}
	}
	std::cout << result;
}
