// 피보나치수 5
// solved
#include <iostream>

int calFibonacci(int present, int next, int n)
{
  if (n == 0)
  {
    return present;
  }

  return calFibonacci(next, next + present, n - 1);
}

int main()
{
  int n;
  std::cin >> n;

  std::cout << calFibonacci(0, 1, n);
}