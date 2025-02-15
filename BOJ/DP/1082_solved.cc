
#include <iostream>
#include <memory.h>

int num_item, max_cost;
int cost[10];
int cache[51][11];		// cache[cost] = cost

int cache_cmp(int const *pnum1, int const *pnum2)
{
	// 우선순위, 개수를 먼저 비교, 개수가 같다면 값이 높은 숫자를 더 많이 보유할 쪽이 크다.
	// 10번 인덱스에는 전체 숫자의 개수, 그 다음은 각 숫자별 개수를 뜻함.
	int num_card1 = pnum1[10];
	int num_card2 = pnum2[10];
	if (num_card1 == pnum1[0])
	{
		num_card1 = 0;
	}
	if (num_card2 == pnum2[0])
	{
		num_card2 = 0;
	}
	if (num_card1 != num_card2)
	{
		return num_card1 - num_card2;
	}
	for (int i = 9; i >= 0; --i)
	{
		if (pnum1[i] != pnum2[i])
			return pnum1[i] - pnum2[i];
	}
	return 0;
}

void print_num(int *num)
{
	if (num[0] == num[10])
	{
		std::cout << 0 << '\n';
		return ;
	}
	for (int i = 9; i >= 0; --i)
	{
		while (num[i] > 0)
		{
			std::cout << i;
			num[i]--;
		}
	}
	std::cout << '\n';
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  memset(cost, 0, sizeof(cost));
  memset(cache, 0, sizeof(cache));

  std::cin >> num_item;
  for (int i = 0; i < num_item; ++i)
  {
	std::cin >> cost[i];
  }
  std::cin >> max_cost;
  // DP
  for (int cur_item = num_item - 1; cur_item >= 0; --cur_item)
  {
	int& cur_item_cost = cost[cur_item];
	for (int cur_cost = 0; cur_cost <= max_cost; ++cur_cost)
	{
		int prev_cost = cur_cost - cur_item_cost;
		if (prev_cost < 0)
			continue ;
		cache[prev_cost][10]++;
		cache[prev_cost][cur_item]++;
		if (cache_cmp(cache[prev_cost], cache[cur_cost]) > 0)
		{
			for (int i = 0; i <= 10; ++i)
			{
				cache[cur_cost][i] = cache[prev_cost][i];
			}
		}
		cache[prev_cost][10]--;
		cache[prev_cost][cur_item]--;
	}
  }
  int max_num_idx = 0;
  // find maximum cost
  for (int idx = 1; idx <= max_cost; ++idx)
  {
	if (cache_cmp(cache[idx], cache[max_num_idx]) > 0)
	{
		max_num_idx = idx;
	}
  }
  // print it
  print_num(cache[max_num_idx]);
}
