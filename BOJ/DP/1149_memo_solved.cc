// memoization.
#include <iostream>
#include <memory.h>

int N;
int price[1001][3]; // painting price = price[home][color], 0 : R, 1 : G, 2 : B.
int cache[1001][3]; // minimum painting price = f(cur home, prev color)

int DP(int houseNum, int prevColor)
{
  int &result = cache[houseNum][prevColor];
  // base case
  if (houseNum == 0)
  {
    return result = 0;
  }
  // cache hit
  else if (result != -1)
  {
    return result;
  }
  // cache miss
  else
  {
    result = 2e9;
    for (int curColor = 0; curColor < 3; ++curColor)
    {
      if (curColor != prevColor)
      {
        result = std::min(result, price[houseNum][curColor] + DP(houseNum - 1, curColor));
      }
    }
    return result;
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
    for (int j = 0; j < 3; ++j)
    {
      std::cin >> price[i][j];
    }
  }

  cache[N][0] = price[N][0] + DP(N - 1, 0);
  cache[N][1] = price[N][1] + DP(N - 1, 1);
  cache[N][2] = price[N][2] + DP(N - 1, 2);
  std::cout << std::min(std::min(cache[N][0], cache[N][1]), cache[N][2]);
}