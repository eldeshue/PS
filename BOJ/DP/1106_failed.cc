// at least num_goal(people), minimum cost
// knnap sack problem, but modified.
// how to know which one is the minimum cost??
// cost can be expanded infinitely...
#include <iostream>
#include <memory.h>

int cities[21][2]; // 0 : cost, 1 : reward(people)
int cache[1101];	// optimized sub problem, 1D is enough
							// cache[num_people] = min_cost

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  for (int i = 1; i <= 1100; ++i)
	cache[i] = 1000000000;
  cache[0] = 0;

  int num_goal, num_city;
  std::cin >> num_goal >> num_city;
  for (int i = 1; i <= num_city; ++i)
  {
	// cost, people
	std::cin >> cities[i][0] >> cities[i][1];
  }
  //
  for (int i = 1; i <= num_city; ++i)
  {
	int *pcur_city = cities[i];
	for (int cur_people = 1; cur_people <= num_goal + 100; ++cur_people)
	{
		int prev_people = cur_people - pcur_city[1];
		if (prev_people >= 0)
		{
			cache[cur_people] = std::min(cache[cur_people], cache[prev_people] + pcur_city[0]);
		}
	}
  }
  //
  int result = 2147483647;
  for (int i = num_goal; i <= 2 * num_goal; ++i)
  {
	result = std::min(result, cache[i]);
  }
  std::cout << result << '\n';
}
