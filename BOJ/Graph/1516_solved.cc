
#include <iostream>
#include <vector>
#include <queue>
#include <memory.h>

std::queue<int> Q;
std::vector<int> graph[501];
int parent_count[501];
int each_build_time[501];
long long total_build_time[501];

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  memset(parent_count, 0, sizeof(parent_count));
  memset(each_build_time, 0, sizeof(each_build_time));
  memset(total_build_time, 0, sizeof(total_build_time));

  int num_building;
  std::cin >> num_building;
  for (int i = 1; i <= num_building; ++i)
  {
	std::cin >> each_build_time[i];
	int parent;
	std::cin >> parent;
	while (parent != -1)
	{
		graph[parent].push_back(i);
		parent_count[i]++;
		std::cin >> parent;
	}
	if (parent_count[i] == 0)
	{
		Q.push(i);
		total_build_time[i] = each_build_time[i];
	}
  }
  // topological sort.
  while (!Q.empty())
  {
	int cur_build = Q.front();
	Q.pop();
	for (const auto& next_build : graph[cur_build])
	{
		parent_count[next_build]--;
		total_build_time[next_build] = std::max(total_build_time[next_build],
		total_build_time[cur_build] + each_build_time[next_build]);
		if (parent_count[next_build] == 0)
		{
			Q.push(next_build);
		}
	}
  }
  // output
  for (int i = 1; i <= num_building; ++i)
  {
	std::cout << total_build_time[i] << '\n';
  }
}
