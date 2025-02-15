// DP
// making 1.
// O(n).
#include <iostream>

int memo[1000001];
int goal;

void memoize(int val)
{
  int cnt = memo[val];
  cnt++;
  // + 1
  int tgt = val + 1;
  if (tgt <= goal)
    if (memo[tgt] > cnt)
    {
      memo[tgt] = cnt;
    }
  // * 2
  tgt = val * 2;
  if (tgt <= goal)
    if (memo[tgt] > cnt)
    {
      memo[tgt] = cnt;
    }
  // * 3
  tgt = val * 3;
  if (tgt <= goal)
    if (memo[tgt] > cnt)
    {
      memo[tgt] = cnt;
    }
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> goal;
  std::fill_n(memo, goal + 1, 1000000);
  memo[1] = 0;
  for (int i = 1; i < goal; ++i)
  {
    memoize(i);
  }
  std::cout << memo[goal];
}