// using memoization, lazy evaluation
#include <iostream>
#include <memory.h>

long int fibonacci[91];

long int calFibonacci(int n)
{
  if (n == 0)
  {
    return 0;
  }
  else if (n == 1)
  {
    return 1;
  }
  else if (fibonacci[n] > 0)
  {
    return fibonacci[n];
  }
  else
  {
    return fibonacci[n] = calFibonacci(n - 1) + calFibonacci(n - 2);
  }
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  memset(fibonacci, -1, 91 * sizeof(long int));
  int N;
  std::cin >> N;
  std::cout << calFibonacci(N);
}