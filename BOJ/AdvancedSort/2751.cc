// 수정렬
// solved
// 개선된 정렬 알고리즘을 이용한 정렬
// 간편한 선형 자료 정렬에는 표준 라이브러리가 제공하는 정렬 알고리즘을 사용하면 편하다.
// std::sort(시작 itr, 끝 itr) : 좌측 포함, 우측 미포함, quick sort기반, 안정성 이슈
// std::stable_sort(left, right) : 위와 마찬가지, 하지만 merge sort기반, 안정적임.
#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
  int n;
  std::cin >> n;
  std::vector<int> vec(n);

  for (auto &elem : vec)
  {
    std::cin >> elem;
  }

  std::sort(vec.begin(), vec.end());

  for (const auto &elem : vec)
  {
    std::cout << elem << "\n";
  }
}