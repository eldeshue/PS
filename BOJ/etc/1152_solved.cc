#include <iostream>
#include <sstream>
#include <string>

int count = 0;
std::string input;
std::string temp;

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::getline(std::cin, input);
  std::istringstream istream(input);
  while (istream >> temp)
  {
    count++;
  }
  std::cout << count;
}