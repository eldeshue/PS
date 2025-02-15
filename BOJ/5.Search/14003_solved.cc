
#include <iostream>
#include <algorithm>
#include <array>

int N;
int buffer[1000000];                  // 4B * 1M = 4MB
std::array<int, 1000000> curEndVal;   // 4B * 1M = 4MB
std::array<int, 1000000> curEndIndex; // 4MB, because total amount of index is 1M
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
  curEndIndex[endPos] = 0;
  curEndVal[endPos] = buffer[0];
  for (int i = 1; i < N; ++i) // O ( N )
  {
    if (buffer[i] > curEndVal[endPos]) // expand LIS
    {
      endPos++;
      curEndIndex[i] = endPos;
      curEndVal[endPos] = buffer[i];
    }
    else // update final numbers
    {
      // lower_bound : O( log N )
      int tempPos = std::lower_bound(curEndVal.begin(), curEndVal.begin() + endPos, buffer[i]) - curEndVal.begin();
      curEndIndex[i] = tempPos;
      curEndVal[tempPos] = buffer[i];
    }
  } // total, O ( N log N )
  std::cout << endPos + 1 << "\n";
  //
  int pos = endPos;
  int prevVal = curEndVal[endPos] + 1;
  for (int i = N - 1; i >= 0; --i) // O( N ), because total size of end Index is N
  {
    if (curEndIndex[i] == pos && buffer[i] < prevVal)
    {
      curEndVal[pos] = buffer[i];
      prevVal = buffer[i];
      pos--;
    }
  }

  for (int i = 0; i <= endPos; ++i)
  {
    std::cout << curEndVal[i] << " ";
  }
}
