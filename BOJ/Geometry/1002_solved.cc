
#include <iostream>
#include <cmath>

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int x1, y1, r1, x2, y2, r2, testNum;
  std::cin >> testNum;
  for (int i = 0; i < testNum; ++i)
  {
    std::cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
    double dist = std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2));

    double max = std::max((double)std::max(r1, r2), dist);
    max *= 2;
    double sum = dist + r1 + r2;

    if (max < sum)
    {
      // 삼각형이 성립 하면 2개
      std::cout << "2\n";
    }
    else if (max == sum)
    {
      if (dist == 0)
      {
        // 하나의 선분인데, dist 가 0이면 무한
        std::cout << "-1\n";
      }
      else
      {
        // 하나의 선분을 이루면 1개
        std::cout << "1\n";
      }
    }
    else
    {
      // 하나의 선분도 못이루면 0개
      std::cout << "0\n";
    }
  }
}