
#include <iostream>
#include <unordered_map>
#include <string>

std::unordered_map<std::string, std::string> pkmonDict;

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int numPkmon, numTest;
  std::string input;
  std::cin >> numPkmon >> numTest;
  for (int i = 1; i <= numPkmon; ++i)
  {
    std::cin >> input;
    pkmonDict.insert(std::make_pair(input, std::to_string(i)));
    pkmonDict.insert(std::make_pair(std::to_string(i), input));
  }

  // test
  for (int i = 0; i < numTest; ++i)
  {
    std::cin >> input;
    std::cout << pkmonDict[input] << "\n";
  }
}