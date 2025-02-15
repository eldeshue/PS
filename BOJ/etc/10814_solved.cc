
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

int N;
std::vector<std::pair<std::string, int>> buffer;

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::string name;
  int age;
  std::cin >> N;
  for (int i = 0; i < N; ++i)
  {
    std::cin >> age >> name;
    buffer.push_back(std::make_pair(name, age));
  }

  std::stable_sort(buffer.begin(), buffer.end(),
                   [](const std::pair<std::string, int> &p1,
                      const std::pair<std::string, int> &p2) -> bool
                   {
                     return p1.second < p2.second;
                   });
  for (const auto &p : buffer)
  {
    std::cout << p.second << " " << p.first << "\n";
  }
}