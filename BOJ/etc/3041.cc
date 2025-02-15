
#include <iostream>

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int result = 0;
  char input;
  for (int i = 0; i < 16; ++i)
  {
    std::cin >> input;
    if (input == '.')
    {
      continue;
    }
    input -= 'A';
    int curX = i / 4;
    int curY = i % 4;
    int nomX = input / 4;
    int nomY = input % 4;
    result += std::abs(curX - nomX) + std::abs(curY - nomY);
  }

  std::cout << result;
}