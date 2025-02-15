// 다각형의 면적
// 다각형을 삼각형들로 분할하고, 각 삼각형의 넓이의 합으로 전체 넓이를 구한다.
// 삼각형의 넓이는 외적으로 구한다.
//
// 절대값의 도입으로 방향의 모호함을 극복했음.
// 문제 해설을 본 결과, 오목 다각형도 볼록 다각형과 동일한 방법으로 풀이하면 됨. 
#include <iostream>
#include <cmath>
#include <vector>

typedef std::pair<long long, long long> point, vec;
std::vector<point> Buffer;
int N;
double totalSum = 0;

double calTri(const point &p1, const point &p2, const point &p3)
{
  // p2 is left, p3 is right
  vec r(p3.first - p1.first, p3.second - p1.second);
  vec l(p2.first - p1.first, p2.second - p1.second);
  return r.first * l.second - r.second * l.first;
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
    Buffer.push_back(point(x, y));
  }

  /////////////
  for(int i = 1; i < N - 1; ++i)
  {
      totalSum += calTri(Buffer[0], Buffer[i], Buffer[i + 1]);
  }
  /////////////

  std::cout << std::fixed;
  std::cout.precision(1);
  totalSum = round(5 * totalSum);
  std::cout << std::abs(totalSum) / 10;
}