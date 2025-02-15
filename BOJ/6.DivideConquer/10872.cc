// 팩토리얼
// solved
#include <iostream>

int calFactorial(int n)
{
  if (n == 0)
  {
    return 1;
  }

  return n * calFactorial(n - 1);
}

int main()
{
  int n;
  std::cin >> n;

  std::cout << calFactorial(n);
}