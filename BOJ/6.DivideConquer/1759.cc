// 암호만들기
// solved
#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

int main()
{
  int L, C;
  std::cin >> L >> C;
  std::vector<char> rsc(C);
  std::vector<char> rst(L);
  for (auto &elem : rsc)
  {
    std::cin >> elem;
  }
  std::sort(rsc.begin(), rsc.end(), [&](char c1, char c2) -> bool
            { return c1 < c2; });

  std::function<void(int, int, int, int)> createPW = [&](int rst_index, int rsc_index, int conso, int gather) -> void
  {
    // consonant : 자음, gather : 모음
    if (rst_index == L)
    {
      if (conso >= 2 && gather >= 1)
      {
        for (const auto &elem : rst)
        {
          std::cout << elem;
        }
        std::cout << std::endl;
      }
      return;
    }
    else if (rsc_index >= C)
    {
      return;
    }
    else
    {
      // 추가하는 경우
      char temp = rsc[rsc_index];
      rst[rst_index] = temp;
      switch (temp)
      {
      case 'a':
      case 'e':
      case 'i':
      case 'o':
      case 'u':
        createPW(rst_index + 1, rsc_index + 1, conso, gather + 1);
        break;
      default:
        createPW(rst_index + 1, rsc_index + 1, conso + 1, gather);
        break;
      }
      // 추가하지 않는 경우
      createPW(rst_index, rsc_index + 1, conso, gather);
    }
  };

  createPW(0, 0, 0, 0);
}