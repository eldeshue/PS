
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
/*
	그래프를 분할하라
	인접한 노드는 1 차이나는 그룹에 속해야 한다
	최대 몇 개의 그룹으로 분할할 수 있는가?
	불가능하면 -1
	트리라면 트리의 지름
	사이클의 존재가 문제의 핵심이 되는 듯.

	사이클인데, 홀수개 노드로 이루어진 사이클은 분할 불가능
	사이클인데, 짝수개면 분할 가능함

	bfs 두번 돌려서 유사 지름 구하기

	그래프가 불연속일 가능성 존재함.
	말인 즉슨 여러 연결요소로 분할 가능함
*/
#pragma GCC optimize("03")
#pragma GCC target("avx")
#pragma GCC target("-fsplit-loops")
#include <queue>
#include <numeric>
#include <functional>
class Solution
{
public:
	// solution method
	int magnificentSets(int n, vector<vector<int>>& edges) {
		// build graph
		vector<vector<unsigned int>> graph(n + 1, vector<unsigned int>(n + 1, 2e9));
		for (auto const& e : edges)
		{
			graph[e[0]][e[1]] = 1;
			graph[e[1]][e[0]] = 1;
		}

		// floyd-warshall
		// diameter in connected component
		for (int mid = 1; mid <= n; ++mid)	// pick mid
		{
			for (int start = 1; start < n; ++start)	// pick start
			{
				for (int end = start + 1; end <= n; ++end)	// pick end
				{
					graph[start][end] = min(graph[start][end], graph[start][mid] + graph[mid][end]);
					graph[end][start] = graph[start][end];
				}
			}
		}
		for (int i = 1; i <= n; ++i)
			graph[i][0] = accumulate(graph[i].begin(), graph[i].end(), 0U, [](unsigned int acc, unsigned int n) {
			if (n == 2e9)
				return acc;
			return max(acc, n);
				});

		// dfs
		int result = 0;
		vector<int> arrival(n + 1, -1);
		function<unsigned int(int const)> findMaxDist = [&](int const curNode) {
			unsigned int maxDist = graph[curNode][0];
			for (int nextNode = 1; nextNode <= n; ++nextNode)
			{
				if (graph[curNode][nextNode] == 1 && arrival[nextNode] != -1 && !((arrival[curNode] - arrival[nextNode]) & 1))	// visited, check odd
				{
					// compare arrival time
					maxDist = -1;
				}
				else if (graph[curNode][nextNode] == 1 && arrival[nextNode] == -1)
				{
					// search next
					arrival[nextNode] = arrival[curNode] + 1;
					maxDist = max(maxDist, findMaxDist(nextNode));
				}
			}
			return maxDist;
			};
		for (int start = 1; start <= n; ++start)
		{
			if (arrival[start] == -1)
			{
				// dfs
				arrival[start] = 0;
				int const localMaxDist = findMaxDist(start);
				// odd cycle found
				if (localMaxDist == -1)
					return localMaxDist;
				result += localMaxDist + 1;
			}
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

	vector<pair<int, int>> input = { {9,16},{8,3},{20,21},{12,16},{14,3},{7,21},{22,3},{22,18},{11,16},{25,4},{2,4},{14,21},{23,3},{17,3},{2,16},{24,16},{13,4},{10,21},{7,4},{9,18},{14,18},{14,4},{14,16},{1,3},{25,18},{17,4},{1,16},{23,4},{2,21},{5,16},{24,18},{20,18},{19,16},{24,21},{9,3},{24,3},{19,18},{25,16},{19,21},{6,3},{26,18},{5,21},{20,16},{2,3},{10,18},{26,16},{8,4},{11,21},{23,16},{13,16},{25,3},{7,18},{19,3},{20,4},{26,3},{23,18},{15,18},{17,18},{10,16},{26,21},{23,21},{7,16},{8,18},{10,4},{24,4},{7,3},{11,18},{9,4},{26,4},{13,21},{22,16},{22,21},{20,3},{6,18},{9,21},{10,3},{22,4},{1,18},{25,21},{11,4},{1,21},{15,3},{1,4},{15,16},{2,18},{13,3},{8,21},{13,18},{11,3},{15,21},{8,16},{17,16},{15,4},{12,3},{6,4},{17,21},{5,18},{6,16},{6,21},{12,4},{19,4},{5,3},{12,21},{5,4} };

	std::sort(input.begin(), input.end());

	for (auto const [x, y] : input)
		std::cout << x << ' ' << y << '\n';
}
