
#include <iostream>

long int cache[1001]; // f(n) = f(n - 1) + 2 * f(n - 2)
int N;

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  cache[1] = 1;
  cache[2] = 3;

  std::cin >> N;
  for (int i = 3; i <= N; ++i)
  {
    cache[i] = cache[i - 1] % 10007 + (2 * cache[i - 2]) % 10007;
  }
  std::cout << cache[N] % 10007;
}