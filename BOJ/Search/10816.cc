// number cards 2
#include <iostream>
#include <map>

std::map<int, int> standard; // 기준
int result[500000];          // 비교 대상

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  // input
  int m, n, temp;
  std::cin >> n;
  for (int i = 0; i < n; ++i)
  {
    std::cin >> temp;
    if (standard.find(temp) != standard.end())
    {
      ++standard[temp];
    }
    else // new
    {
      standard.insert(std::make_pair(temp, 1));
    }
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

    if (standard.find(target) != standard.end())
    {
      result[i] = standard[target];
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