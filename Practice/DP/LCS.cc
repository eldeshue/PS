// Longest Common Subsequence
// 최장 공통 수열, using memoization
// ex ) L a tra v i ata, Avatarian => avata
#include <iostream>
#include <memory.h>
#include <string>

int cache[1001][1001];
std::string str1, str2;
int max1, max2;

int LCS() // recursing
{
  int result = 0;
  for (int i = 0; i < max1; ++i)
  {
    for (int j = 0; j < max2; ++j)
    {
      if (str1.at(i + 1) == str2.at(j + 1))
      {
        cache[i + 1][j + 1] = 1 + cache[i][j];
      }
      /************************************************************************/
      // 사실상 해당 문제의 핵심 구조, DP의 개념이 나타나 있는 부분
      // 과거에 캐싱해두었다는 사실을 이해하지 못했다.
      // 이 부분이 캐싱되었는지를 이해하지 못하니 재사용도 못했다.
      // 지능의 문제가 아닌가?
      else
      {
        cache[i + 1][j + 1] = std::max(cache[i][j + 1], cache[i + 1][j]);
      }
      /************************************************************************/

      result = std::max(result, cache[i + 1][j + 1]);
    }
  }
  return result;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  for (int i = 0; i < 1001; ++i)
  {
    memset(cache, 0, 1001 * sizeof(int));
  }

  std::cin >> str1 >> str2;
  max1 = str1.size();
  max2 = str2.size();
  str1 = " " + str1;
  str2 = " " + str2;
  std::cout << LCS();
}