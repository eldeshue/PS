
#include <iostream>
#include <memory.h>

int cache[101][100001]; // cache[obj][weight] = max_value
int objects[101][2];

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  memset(cache, 0, sizeof(cache));
  memset(objects, 0, sizeof(objects));

  int obj_num, max_weight;
  std::cin >> obj_num >> max_weight;
  for (int i = 1; i <= obj_num; ++i)
  {
    std::cin >> objects[i][0] >> objects[i][1];
  }
  for (int obj_idx = 1; obj_idx <= obj_num; ++obj_idx)
  {
    for (int cur_wght = 1; cur_wght <= max_weight; ++cur_wght)
    {
      int diag_wght = cur_wght - objects[obj_idx][0];
      if (diag_wght >= 0)
      {
        cache[obj_idx][cur_wght] = std::max(cache[obj_idx - 1][cur_wght],
                                            cache[obj_idx - 1][diag_wght] + objects[obj_idx][1]);
      }
      else
      {
        cache[obj_idx][cur_wght] = cache[obj_idx - 1][cur_wght];
      }
    }
  }
  std::cout << cache[obj_num][max_weight];
}
