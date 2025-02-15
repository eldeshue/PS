// printing star
// solved
#include <iostream>

bool ok(int x, int y, int l)
{
  if (l == 0)
  {
    return true;
  }

  int x_quot = x / l; // 몫 quotient
  int y_quot = y / l;
  if ((x_quot == 1) && (y_quot == 1))
  {
    return false;
  }
  else
  {
    return ok(x % l, y % l, l / 3);
  }
}

int main()
{
  int N;
  std::cin >> N;

  for (int i = 0; i < N; ++i)
  {
    for (int j = 0; j < N; ++j)
    {
      if (ok(i, j, N / 3))
      {
        std::cout << "*";
      }
      else
      {
        std::cout << " ";
      }
    }
    std::cout << std::endl;
  }
}