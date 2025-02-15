
#include <iostream>
#include <cmath>
#include <deque>

typedef std::pair<long long, long long> point, vec;
std::deque<point> roundBuffer;
int N;
double totalSum = 0;

double calTri(const point &p1, const point &p2, const point &p3)
{
  // p2 is left, p3 is right
  vec r(p3.first - p1.first, p3.second - p1.second);
  vec l(p2.first - p1.first, p2.second - p1.second);
  return r.second * l.first - r.first * l.second;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::cin >> N;
  for (int i = 0; i < N; ++i)
  {
    long long x, y;
    std::cin >> x >> y;
    roundBuffer.push_back(point(x, y));
  }
  /////////////
  while (N > 2)
  {
    point curPoint = roundBuffer.front();
    roundBuffer.pop_front();
    double curTri = calTri(curPoint, roundBuffer.back(), roundBuffer.front());
    if (curTri > 0)
    {
      totalSum += curTri;
      N--;
    }
    else // revolve
    {
      roundBuffer.push_back(curPoint);
    }
  }

  /////////////
  std::cout << std::fixed;
  std::cout.precision(1);
  totalSum = round(5 * totalSum);
  std::cout << totalSum / 10;
}