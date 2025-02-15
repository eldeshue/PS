// pelindrome?
// Tabulation.
#include <iostream>

int N;
int cache[2001][2001];
int numbers[2001];

void tabulate()
{
  // base case
  for (int i = 1; i <= N; ++i)
  {
    cache[i][i] = 1;
  }
  for (int i = 1; i <= N - 1; ++i)
  {
    if (numbers[i] == numbers[i + 1])
    {
      cache[i][i + 1] = 1;
    }
    else
    {
      cache[i][i + 1] = 0;
    }
  }
  for (int i = 2; i < N; ++i)
  {
    for (int j = 1; j <= N - i; ++j)
    {
      if (numbers[j] == numbers[j + i] && cache[j + 1][j + i - 1] == 1)
      {
        cache[j][j + i] = 1;
      }
      else
      {
        cache[j][j + i] = 0;
      }
    }
  }
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::cin >> N;
  for (int i = 1; i <= N; ++i)
  {
    std::cin >> numbers[i];
  }
  tabulate();
  int M, S, E;
  std::cin >> M;
  for (int i = 0; i < M; ++i)
  {
    std::cin >> S >> E;
    std::cout << cache[S][E] << "\n";
  }
}