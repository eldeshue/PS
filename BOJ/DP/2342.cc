
#include <iostream>
#include <memory.h>
#include <tuple>
#include <queue>

int N = 1;
int command[100001];
unsigned int cache[100001][5][5]; // cache[ stage ][ left ][ right ]

int movCost(const int prev, const int next)
{
  if (prev == 0)
  {
    return 2;
  }
  else if (prev == next)
  {
    return 1;
  }
  else if (std::abs(prev - next) == 2)
  {
    return 4;
  }
  else
  {
    return 3;
  }
}

unsigned int DP(int curPos, int curL, int curR)
{
  if (curPos == N) // base case
  {
    return 0;
  }
  else if (cache[curPos][curL][curR] != -1)
  {
    return cache[curPos][curL][curR];
  }
  else
  {
    unsigned int nextL = movCost(curL, command[curPos]) + DP(curPos + 1, command[curPos], curR);
    unsigned int nextR = movCost(curR, command[curPos]) + DP(curPos + 1, curL, command[curPos]);
    return cache[curPos][curL][curR] = std::min(nextL, nextR);
  }
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  memset(cache, -1, sizeof(cache));

  int input;
  std::cin >> input;
  while (input != 0)
  {
    command[N] = input;
    std::cin >> input;
    N++;
  }

  //
  std::cout << DP(1, 0, 0);
}