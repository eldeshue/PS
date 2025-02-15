
#include <iostream>
#include <string>
#include <set>

std::set<std::string> unheard;
std::set<std::string> unseen;
std::set<std::string> unheardunseen;

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int N, M;
  std::string temp;
  std::cin >> N >> M;
  for (int i = 0; i < N; ++i)
  {
    std::cin >> temp;
    unheard.insert(temp);
  }
  for (int j = 0; j < M; ++j)
  {
    std::cin >> temp;
    unseen.insert(temp);
  }

  for (const auto &elem : unseen)
  {
    if (unheard.find(elem) != unheard.end())
    {
      unheardunseen.insert(elem);
    }
  }

  std::cout << unheardunseen.size() << "\n";
  for (const auto &elem : unheardunseen)
  {
    std::cout << elem << "\n";
  }
}