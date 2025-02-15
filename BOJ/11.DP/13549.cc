
#include <iostream>
#include <queue>
#include <memory.h>

using uint = unsigned int;
uint start, end;
uint cache[200001];

uint BFS()
{
  uint cur_pos, nex_pos, cur_time;
  std::queue<uint> Q;
  cache[start] = 0;
  Q.push(start);

  while (!Q.empty())
  {
	cur_pos = Q.front();
	cur_time = cache[cur_pos];
	if (cur_time == -1)
		continue;
	if (cur_pos == end)
		break;
	Q.pop();
	nex_pos = cur_pos * 2;
	if (cur_pos < end && cur_time < cache[nex_pos])
	{
		cache[nex_pos] = cur_time;
		Q.push(nex_pos);
	}
	nex_pos = cur_pos + 1;
	if (cur_pos < end && cur_time + 1 < cache[nex_pos])
	{
		cache[nex_pos] = cur_time + 1;
		Q.push(nex_pos);
	}
	nex_pos = cur_pos - 1;
	if (cur_pos > 0 && cur_time + 1 < cache[nex_pos])
	{
		cache[nex_pos] = cur_time + 1;
		Q.push(nex_pos);
	}
  }
  return cache[cur_pos];
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  memset(cache, -1, sizeof(cache));

  std::cin >> start >> end;
  BFS();
  std::cout << cache[end];
}
