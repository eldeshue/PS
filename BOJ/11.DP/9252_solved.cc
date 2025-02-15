
#include <iostream>
#include <cmath>
#include <memory.h>
#include <string>
#include <stack>

std::string str1, str2;
std::stack<char> result;
int lengthCache[1001][1001];

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  memset(lengthCache, 0, sizeof(lengthCache));
  // tabulation
  std::cin >> str1 >> str2;
  int str1_size = str1.size();
  int str2_size = str2.size();
  str1 = ' ' + str1;
  str2 = ' ' + str2;
  for (int pos1 = 1; pos1 <= str1_size; ++pos1)
  {
    for (int pos2 = 1; pos2 <= str2_size; ++pos2)
    {
      if (str1.at(pos1) == str2.at(pos2))
      {
        lengthCache[pos1][pos2] = lengthCache[pos1 - 1][pos2 - 1] + 1;
      }
      else
      {
        lengthCache[pos1][pos2] = std::max(lengthCache[pos1 - 1][pos2],
                                           lengthCache[pos1][pos2 - 1]);
      }
    }
  }
  //********************** tracing back to find the LCS. ************************//
  int p1 = str1_size, p2 = str2_size, i = 0;
  while (i != lengthCache[str1_size][str2_size])
  {
    if (str1.at(p1) == str2.at(p2))
    {
      result.push(str1.at(p1));
      p1--;
      p2--;
      i++;
    }
    else
    {
      if (lengthCache[p1 - 1][p2] > lengthCache[p1][p2 - 1])
      {
        p1--;
      }
      else
      {
        p2--;
      }
    }
  }
  //********************** tracing back to find the LCS. ************************//

  std::cout << lengthCache[str1_size][str2_size] << "\n";
  while (!result.empty())
  {
    std::cout << result.top();
    result.pop();
  }
}