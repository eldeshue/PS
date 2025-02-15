
#include <iostream>
#include <deque>

int N;
std::deque<int> DQ;

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::cin >> N;
  for (int i = N; i >= 1; --i)
  {
    DQ.push_front(i);
  }

  while (DQ.size() != 1)
  {
    DQ.pop_front();
    DQ.push_back(DQ.front());
    DQ.pop_front();
  }

  std::cout << DQ.front();
}