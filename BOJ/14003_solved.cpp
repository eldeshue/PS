
#include <iostream>
#include <algorithm>
#include <vector>
#include <array>

int N;
int buffer[1000000];                              // 4B * 1M = 4MB
std::array<int, 1000000> curEndVal;               // 4B * 1M = 4MB
std::array<std::vector<int>, 1000000> endIndex;   // 4MB, because total amount of index is 1M
                                                  // total, 12MB

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
  int endPos = 0;
  endIndex[endPos].push_back(0);
  curEndVal[endPos] = buffer[0];
  for (int i = 1; i < N; ++i) // O ( N )
  {
    if (buffer[i] > curEndVal[endPos]) // expand LIS
    {
        endPos++;
        endIndex[endPos].push_back(i);
        curEndVal[endPos] = buffer[i];
    }
    else // update final numbers
    {
        // lower_bound : O( log N )
        int tempPos = std::lower_bound(curEndVal.begin(), curEndVal.begin() + endPos, buffer[i]) - curEndVal.begin();
        endIndex[tempPos].push_back(i);
        curEndVal[tempPos] = buffer[i];
    }
  } // total, O ( N log N )
  std::cout << endPos + 1 << "\n";
  //

  int prevIndex = endIndex[endPos].back();
  for (int i = endPos - 1; i >= 0; --i)    // O( N ), because total size of end Index is N
  {
      int j = endIndex[i].size() - 1;
      while (endIndex[i][j] > prevIndex)
      {
          j--;
      }
      prevIndex = endIndex[i][j];
      curEndVal[i] = buffer[prevIndex];
  }

  for(int i = 0; i <= endPos; ++i)
  {
      std::cout << curEndVal[i] << " ";
  }
}
