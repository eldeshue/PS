
#include <iostream>

int h, m;

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::cin >> h >> m;
  if (m >= 45)
  {
    m -= 45;
  }
  else
  {
    m += 60;
    m -= 45;
    if (h == 0)
    {
      h = 23;
    }
    else
    {
      --h;
    }
  }
  std::cout << h << " " << m;
}