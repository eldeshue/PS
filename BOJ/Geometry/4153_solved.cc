
#include <iostream>

int len[3];

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  while (true)
  {
    int max = 0;
    int total = 0;
    for (int i = 0; i < 3; ++i)
    {
      std::cin >> len[i];
      total += len[i] * len[i];
      max = std::max(max, len[i]);
    }

    if (len[0] == len[1] && len[0] == len[2] && len[0] == 0)
    {
      break;
    }

    if (2 * max * max == total)
    {
      std::cout << "right\n";
    }
    else
    {
      std::cout << "wrong\n";
    }
  }

  return 0;
}