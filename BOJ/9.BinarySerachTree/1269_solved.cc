// 대칭 차집합, XOR
#include <iostream>
#include <set>

std::set<int> A;
std::set<int> B;

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int numA, numB, input;
  std::cin >> numA >> numB;
  for (int i = 0; i < numA; ++i)
  {
    std::cin >> input;
    A.insert(input);
  }
  for (int i = 0; i < numB; ++i)
  {
    std::cin >> input;
    B.insert(input);
  }
  // get number of intersection.
  int numIntersec = 0;
  for (const auto &elemA : A)
  {
    if (B.find(elemA) != B.end())
    {
      numIntersec++;
    }
  }

  std::cout << A.size() + B.size() - 2 * numIntersec;
}