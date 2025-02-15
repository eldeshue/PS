
#include <iostream>
#include <vector>

int N, max = 0;
float total = 0;

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int temp;
  std::cin >> N;
  for (int i = 0; i < N; ++i)
  {
    std::cin >> temp;
    total += temp;
    max = std::max(max, temp);
  }
  std::cout << total * 100 / N / max;
}