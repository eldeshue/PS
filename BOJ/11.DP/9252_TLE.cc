
#include <iostream>
#include <string>

std::string strVec[1000000];
int cache[1001][1001];
std::string str1, str2;

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  strVec[0] = std::string();
  for (int i = 0; i < str1.size(); ++i)
  {
    for (int j = 0; j < str2.size(); ++j)
    {
      cache[i][j] = 0;
    }
  }

  // tabulation.
  int nextVecPos = 1;
  std::cin >> str1 >> str2;
  int str1_size = str1.size(), str2_size = str2.size();
  for (int pos1 = 0; pos1 < str1_size; ++pos1)
  {
    for (int pos2 = 0; pos2 < str2_size; ++pos2)
    {
      std::string &curLCS = strVec[cache[pos1][pos2]];
      std::string &rLCS = strVec[cache[pos1][pos2 + 1]];
      std::string &dwLCS = strVec[cache[pos1 + 1][pos2]];
      std::string &diagLCS = strVec[cache[pos1 + 1][pos2 + 1]];
      // if same
      if (str1.at(pos1) == str2.at(pos2)) //&& curLCS.size() + 1 > diagLCS.size())
      {
        strVec[nextVecPos] = curLCS + str1.at(pos1);
        cache[pos1 + 1][pos2 + 1] = nextVecPos;
        nextVecPos++;
      }
      if (curLCS.size() > rLCS.size())
      {
        cache[pos1][pos2 + 1] = cache[pos1][pos2];
      }
      if (curLCS.size() > dwLCS.size())
      {
        cache[pos1 + 1][pos2] = cache[pos1][pos2];
      }
    }
  }

  std::string &result =
      (strVec[cache[str1.size() - 1][str2.size()]].size() <
       strVec[cache[str1.size()][str2.size() - 1]].size())
          ? strVec[cache[str1.size()][str2.size() - 1]]
          : strVec[cache[str1.size() - 1][str2.size()]];

  std::cout << result.size() << "\n";
  if (result.size() != 0)
  {
    std::cout << result;
  }
}
