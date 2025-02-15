
#include <iostream>

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int x, y;
  std::cin >> x >> y;
  if (x > 0) // 1, 4
  {
    if (y > 0)
    {
      std::cout << 1;
    }
    else
    {
      std::cout << 4;
    }
  }
  else // 2, 3
  {
    if (y > 0)
    {
      std::cout << 2;
    }
    else
    {
      std::cout << 3;
    }
  }
}