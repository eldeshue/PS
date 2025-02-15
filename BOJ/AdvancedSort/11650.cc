// solved.
// 2종의 우선순위를 바탕으로 정렬하는 문제.
// 정렬 자체는 std::sort를 통한 quick sort로 해결함.
// 정렬의 기준이 되는 우선순위는 람다식을 이용하여 구조체의 우열판단을 구현.
#include <iostream>
#include <algorithm>
#include <vector>

typedef struct POINT
{
  int x;
  int y;
} POINT;

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int N;
  std::cin >> N;
  std::vector<POINT> vec(N);
  for (auto &elem : vec)
  {
    std::cin >> elem.x >> elem.y;
  }

  std::sort(vec.begin(), vec.end(), [&](POINT p1, POINT p2) -> bool
            {
              if (p1.x == p2.x)
              {
                return p1.y < p2.y;
              }
              return p1.x < p2.x; });

  for (const auto &elem : vec)
  {
    std::cout << elem.x << " " << elem.y << "\n";
  }
}