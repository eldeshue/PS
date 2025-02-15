// number cards
// solved
#include <iostream>
#include <set>

std::set<int> standard; // 기준
int result[500000];     // 비교 대상

int main()
{
  // input
  int m, n, temp;
  std::cin >> n;
  for (int i = 0; i < n; ++i)
  {
    std::cin >> temp;
    standard.insert(temp);
  }
  std::cin >> m;
  for (int i = 0; i < m; ++i)
  {
    std::cin >> result[i];
  }
  // processing
  for (int i = 0; i < m; ++i)
  {
    int target = result[i];

    if (standard.find(target) != standard.end()) // included
    {
      result[i] = 1;
    }
    else
    {
      result[i] = 0;
    }
  }

  // output
  for (int i = 0; i < m; ++i)
  {
    std::cout << result[i] << " ";
  }
  std::cout << std::endl;
}