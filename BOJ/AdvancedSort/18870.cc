// solved
#include <iostream>
#include <vector>
#include <map>

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int N, temp;
  std::cin >> N;
  std::vector<int> vec(N);
  std::map<int, int> map; // key를 기준으로 자동으로 정렬됨
  for (int i = 0; i < N; ++i)
  {
    std::cin >> temp;
    vec[i] = temp;
    if (map.find(temp) == map.end())
    {
      map.insert(std::make_pair(temp, 1));
    }
  }

  // accumulate
  temp = 0;
  int prev_accum_val = 0;
  int prev_val = 0;
  for (auto &elem : map)
  {
    temp = elem.second;
    elem.second = prev_val + prev_accum_val;
    prev_val = temp;
    prev_accum_val = elem.second;
  }

  for (const auto &key : vec)
  {
    std::cout << map[key] << " ";
  }
}