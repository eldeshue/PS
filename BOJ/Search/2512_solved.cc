
#include <iostream>
#include <functional>

int numCity, maxBudget;
int budgets[10000];

int BinSearchMax(int s, int e, std::function<bool(int)> f)
{ // ( ]
  int low = s + 1, high = e;

  while (low != high)
  {
    int mid = (low + high + 1) >> 1;
    f(mid) ? low = mid : high = mid - 1;
  }

  if (low == s)
  {
    return -1;
  }
  else
  {
    return low;
  }
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int max = 0;
  std::cin >> numCity;
  for (int i = 0; i < numCity; ++i)
  {
    std::cin >> budgets[i];
    max = std::max(max, budgets[i]);
  }
  std::cin >> maxBudget;

  auto cond = [&](int val) -> bool
  {
    int total = 0;
    for (const auto &elem : budgets)
    {
      if (elem > val)
      {
        total += val;
      }
      else
      {
        total += elem;
      }
    }

    if (total > maxBudget)
    {
      return false;
    }
    else
    {
      return true;
    }
  };
  std::cout << BinSearchMax(0, max, cond);
}