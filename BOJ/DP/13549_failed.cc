
#include <iostream>
#include <memory.h>

unsigned int start, end;
unsigned int cache[200001];

unsigned int DP(unsigned int cur_pos)
{
	// base case
	if (cur_pos > 200000)
		return -1;
	else if (cache[cur_pos] < (unsigned int)(-1))
		return cache[cur_pos];
	unsigned int tmp, next_time = -1;
	if (cur_pos != 0 && (cur_pos % 2) == 0)
	{
		next_time = std::min(next_time, DP(cur_pos / 2));
	}
	if (cur_pos > 0)
	{
		tmp = DP(cur_pos - 1);
		if (tmp != -1)
			next_time = std::min(next_time, tmp + 1);
	}
	if (cur_pos < 200000)
	{
		tmp = DP(cur_pos + 1);
		if (tmp != -1)
			next_time = std::min(next_time, tmp  + 1);
	}
	return (cache[cur_pos] = next_time);
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  memset(cache, -1, sizeof(cache));

  std::cin >> start >> end;
  // DP
  cache[start] = 0;
  std::cout << DP(end);
}
