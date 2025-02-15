
#include <iostream>
#include <string>
#include <set>

std::set<std::string> currentEmployee;

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int numLog;
  std::string name, log;
  std::cin >> numLog;
  for (int i = 0; i < numLog; ++i)
  {
    std::cin >> name >> log;
    if (log == "enter")
    {
      currentEmployee.insert(name);
    }
    else
    {
      currentEmployee.erase(name);
    }
  }

  for (auto itr = currentEmployee.rbegin(); itr != currentEmployee.rend(); ++itr)
  {
    std::cout << *itr << "\n";
  }
}