
#include <iostream>
#include <algorithm>
#include <vector>

int N;
int buffer[1000000];
std::vector<int> endNums;

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::cin >> N;
  for (int i = 0; i < N; ++i)
  {
    std::cin >> buffer[i];
  }

  //
  endNums.push_back(buffer[0]);
  for (int i = 1; i < N; ++i)
  {
    if (buffer[i] > endNums.back()) // expand LIS
    {
      endNums.push_back(buffer[i]);
    }
    else // update final numbers
    {
      *(std::lower_bound(endNums.begin(), endNums.end(), buffer[i])) = buffer[i];
    }
  }
  //
  std::cout << endNums.size();
}