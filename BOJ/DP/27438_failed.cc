
#include <iostream>
#include <set>

int N;
std::set<unsigned long long int> cache;

void tabulate(int start, int rank)
{
  // how to handle duplicated element???
  // do I have to use set???
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  cache.insert(666);

  std::cin >> N;
  tabulate(2, 4);
  std::set<unsigned long long int>::iterator itr = cache.begin();
  for (int i = 1; i < N; ++i)
  {
    itr++;
  }
  std::cout << *itr;
}