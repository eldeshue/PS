
#include <iostream>
#include <string>

bool is666(const std::string &str)
{
  for (int i = 0; i < str.size() - 2; ++i)
  {
    if (str.substr(i, 3) == "666")
    {
      return true;
    }
  }
  return false;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int N, num = 665, count = 0;
  std::cin >> N;
  while (count != N)
  {
    num++;
    if (is666(std::to_string(num)))
    {
      count++;
    }
  }
  std::cout << num;
}