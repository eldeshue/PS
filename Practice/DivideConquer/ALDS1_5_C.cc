// Koch curve
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#define Pi 3.14159265
typedef struct point
{
  double x;
  double y;
} point;
std::vector<point> result;

void calcKochPoint(point begP, point endP, float length, int depth)
{
  if (depth == 0)
  {
    return;
  }
  int new_length = length / 3;
  int new_depth = depth - 1;
  point p1, p2, p3;
  p1.x = (2 * begP.x + endP.x) / 3;
  p1.y = (2 * begP.y + endP.y) / 3;
  p2.x = (begP.x + endP.x) / 2;
  p2.y = new_length * std::sin(Pi / 3);
  p3.x = (begP.x + 2 * endP.x) / 3;
  p3.y = (begP.y + 2 * endP.y) / 3;
  result.push_back(p1);
  result.push_back(p2);
  result.push_back(p3);

  calcKochPoint(begP, p1, new_length, new_depth);
  calcKochPoint(p1, p2, new_length, new_depth);
  calcKochPoint(p2, p3, new_length, new_depth);
  calcKochPoint(p3, endP, new_length, new_depth);
}

bool compPoint(point p1, point p2)
{
  return p1.x < p2.x;
}

int main()
{
  int n;
  std::cin >> n;
  point begin, end;
  begin.x = 0;
  begin.y = 0;
  end.x = 100;
  end.y = 0;

  result.push_back(begin);
  calcKochPoint(begin, end, 100, n);
  result.push_back(end);

  std::sort(result.begin(), result.end(), compPoint);

  for (auto &elem : result)
  {
    std::cout << elem.x << " " << elem.y << "\n";
  }
  std::cout << std::endl;
}