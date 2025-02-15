
#include <iostream>

int N;
int cache[101][10];

void tabulation()
{
  // initial value setting
  cache[1][0] = 0; // no 0 start
  for (int i = 1; i < 10; ++i)
  {
    cache[1][i] = 1;
  }
  // calculate
  for (int length = 2; length <= N; ++length)
  {
    cache[length][0] = cache[length - 1][1];
    cache[length][9] = cache[length - 1][8];
    for (int endNum = 1; endNum < 9; ++endNum)
    {
      cache[length][endNum] = (cache[length - 1][endNum + 1] + cache[length - 1][endNum - 1]) % 1000000000;
    }
  }
}

int calResult() // sum total
{
  int result = 0;
  for (int i = 0; i < 10; ++i)
  {
    result = (result + cache[N][i]) % 1000000000;
  }
  return result;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::cin >> N;
  tabulation();
  std::cout << calResult();
}