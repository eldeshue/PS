// 실수 연산의 개념을 유의하자!
#include <iostream>
#include <vector>

std::vector<int> buildings;
std::vector<int> count;
int N;

double calSlope(int me, int you)
{
  return ((double)(buildings[you] - buildings[me]) / (you - me));
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cin >> N;
  buildings.resize(N);
  count.resize(N);
  int temp;
  for (int i = 0; i < N; ++i)
  {
    std::cin >> temp;
    buildings[i] = temp;
    count[i] = 0;
  }
  //
  for (int me = 0; me < N - 1; ++me)
  {
    double prev_stiffest_slope = -(2e9);
    for (int you = me + 1; you < N; ++you)
    {
      double currentSlope = calSlope(me, you);
      if (prev_stiffest_slope < currentSlope)
      {
        count[me]++;
        count[you]++;
        prev_stiffest_slope = currentSlope;
      }
    }
  }
  //
  int result = 0;
  for (const auto &elem : count)
  {
    if (result < elem)
    {
      result = elem;
    }
  }
  std::cout << result;
}