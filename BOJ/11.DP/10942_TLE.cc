// pelindrome??
// memoization.
#include <iostream>
#include <memory.h>

int N;
int numbers[2001];
int cache[2001][2001]; // cache[start][end] = -1 unknown, 0 no, 1 yes

int DP(int start, int end)
{
  int &result = cache[start][end];

  if (result != -1) // cache hit
  {
    return result;
  }
  // base case
  else if (start == end) // odd num
  {
    return result = 1;
  }
  else if (start == end - 1) // even
  {
    if (numbers[start] == numbers[end])
    {
      return result = 1;
    }
    else
    {
      return result = 0;
    }
  }
  else // cache miss
  {
    if (numbers[start] == numbers[end])
    {
      return DP(start + 1, end - 1); // so far so good, recurse
    }
    else // nah
    {
      return result = 0;
    }
  }
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  memset(cache, -1, sizeof(cache));

  std::cin >> N;
  for (int i = 1; i <= N; ++i)
  {
    std::cin >> numbers[i];
  }
  int M, S, E;
  std::cin >> M;
  for (int i = 0; i < M; ++i)
  {
    std::cin >> S >> E;
    std::cout << DP(S, E) << "\n";
  }
}