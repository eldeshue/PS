
#include <iostream>
#include <memory.h>

int N;
int cache[1001];

int DP(int n)
{
  if (n == 0 || n == 1) // base case
  {
    return cache[n] = 1;
  }
  else if (cache[n] != 0) // cache hit
  {
    return cache[n];
  }
  else // cache miss
  {
    return cache[n] = (DP(n - 1) + DP(n - 2)) % 10007;
  }
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  memset(cache, 0, sizeof(cache));

  std::cin >> N;
  std::cout << DP(N);
}