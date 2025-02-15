
#include <iostream>
#include <functional>
#include <vector>

int K, N;
std::vector<int> cables;

long long int maxBinarySearch(long long int start, long long int end, std::function<bool(long long int)> cond)
{
  long long int low = start; // not included
  long long int high = end;  // included

  while (low != high)
  {
    long long int mid = (low + high + 1) >> 1;

    if (cond(mid))
    {
      low = mid;
    }
    else
    {
      high = mid - 1;
    }
  }

  if (low == start)
  {
    return -1;
  }
  else
  {
    return low; // maximum cable length
  }
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  long long int total = 0;
  std::cin >> K >> N;
  cables.resize(K);
  for (int i = 0; i < K; ++i)
  {
    std::cin >> cables[i];
    total += cables[i];
  }
  std::function<bool(long long int)> cond = [&](long long int numLength) -> bool
  {
    long long int count = 0;

    for (int i = 0; i < K; ++i)
    {
      count += (cables[i] / numLength);
    }

    if (count >= N)
    {
      return true;
    }
    else
    {
      return false;
    }
  };

  std::cout << maxBinarySearch(0, total / N, cond);
}