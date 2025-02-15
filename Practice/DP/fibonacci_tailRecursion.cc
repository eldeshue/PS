#include <iostream>

int fibonacci(int p, int next, int n)
{
  if (n == 0)
  {
    return p;
  }
  else
  {
    return fibonacci(next, p + next, n - 1);
  }
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int N;
  std::cin >> N;
  std::cout << fibonacci(0, 1, N);
}