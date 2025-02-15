// https://www.acmicpc.net/source/share/2e8b21f265ec49eeae1aecbbf73a2db1
// Problem solving, using Binary Serach

#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
  // input
  int N, C;
  std::cin >> N >> C;
  std::vector<int> X(N);

  // sort the vector to apply Binary Serach
  for (auto &x : X)
  {
    std::cin >> x;
  }
  sort(X.begin(), X.end());

  // define standard
  // 공유기 설치 조건에 대한 함수
  // 공유기의 설치가 가능한 간격인가
  // lim은 설치 최소 간격 -> 해당 lim값을 가지고 공유기를 깔았을 때, C개를 넘는가?
  //
  auto ok = [&](int limit) -> bool
  {
    int prev = -1e9, count = 0; // -1000000000
    for (const auto &elem : X)
    {
      if ((elem - prev) >= limit)
      {
        prev = elem;
        ++count;
      }
    }

    return count >= C;
  };

  // binary search
  int low = 0, high = X.back() - X.front();
  while (high != low)
  {
    int mid = (high + low + 1) >> 1;      // +1 해주는 이유는
    ok(mid) ? low = mid : high = mid - 1; // high에 mid - 1이 가기 때문임
  }

  std::cout << low;
}