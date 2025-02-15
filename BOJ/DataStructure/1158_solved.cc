// Josepus problem
#include <iostream>
#include <queue>
#include <vector>

std::queue<int> Q;

void roundCCW()
{
  Q.push(Q.front());
  Q.pop();
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int N, K;
  std::cin >> N >> K;
  for (int i = 1; i <= N; ++i)
  {
    Q.push(i);
  }
  K--;
  std::cout << "<";
  for (int i = 1; i < N; ++i)
  {
    for (int j = 0; j < K; ++j)
    {
      roundCCW();
    }
    std::cout << Q.front() << ", ";
    Q.pop();
  }
  std::cout << Q.front() << ">";
}