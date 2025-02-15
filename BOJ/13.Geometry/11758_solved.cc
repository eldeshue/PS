// 벡터의 외적 문제.
// 외적의 결과가 양수이면 반시계, 음수이면 시계, 0이면 일직선이다.
#include <iostream>

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int x1, y1, x2, y2, x3, y3;
  std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
  int vx1 = x2 - x1;
  int vy1 = y2 - y1;
  int vx2 = x3 - x2;
  int vy2 = y3 - y2;
  // 외적
  int crossProduct = vx1 * vy2 - vy1 * vx2;
  if (crossProduct > 0)
  {
    std::cout << "1";
  }
  else if (crossProduct == 0)
  {
    std::cout << "0";
  }
  else
  {
    std::cout << "-1";
  }
}