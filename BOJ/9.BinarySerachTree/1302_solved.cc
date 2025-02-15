
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>

typedef std::map<std::string, int>::iterator map_itr;

std::map<std::string, int> sales;
std::vector<map_itr> vec;

bool compPair(map_itr &pair1,
              map_itr &pair2)
{
  if (pair1->second == pair2->second)
  {
    return pair1->first < pair2->first;
  }
  else
  {
    return (pair1->second > pair2->second);
  }
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  // fill sales table
  int N;
  std::string temp;
  std::cin >> N;
  for (int i = 0; i < N; ++i)
  {
    std::cin >> temp;
    if (sales.find(temp) == sales.end())
    {
      sales.insert(std::make_pair(temp, 0));
    }
    else
    {
      sales[temp]++;
    }
  }

  // sort
  // fill the vec to sort
  for (auto itr = sales.begin(); itr != sales.end(); ++itr)
  {
    vec.push_back(itr);
  }
  std::sort(vec.begin(), vec.end(), compPair);

  // get the largest salary
  std::cout << (*vec.begin())->first;
}