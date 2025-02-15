
#include <iostream>
#include <memory.h>
#include <algorithm>
#include <vector>

using ull = unsigned long long;
std::vector<ull> coins;
std::vector<unsigned int> cache(1000000000000001);

void init(const ull target_val)
{
  coins.clear();
  ull pow10 = 1;
  ull pow100 = 25;
  for (; pow10 <= target_val; pow10 *= 10)
  {
    coins.push_back(pow10);
  }
  for (; pow100 <= target_val; pow100 *= 100)
  {
    coins.push_back(pow100);
  }
  for (ull i = 1; i <= 1000000000000000; ++i)
  {
    cache[i] = static_cast<int>(-1);
  }
  cache[0] = 0;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int test_num;
  ull choco_val;
  std::cin >> test_num;
  for (int i = 0; i < test_num; ++i)
  {
    std::cin >> choco_val;
    init(choco_val);
    for (const auto &coin : coins)
    {
      for (ull cur_cost = 0; cur_cost + coin <= choco_val; ++cur_cost)
      {
        cache[cur_cost] = std::min(cache[cur_cost], cache[cur_cost - coin] + 1);
      }
    }
    std::cout << cache[choco_val] << '\n';
  }
}
