
#include <iostream>
#include <vector>

int N, M;

void DFS(std::vector<int> vec, int prevNum, int pos)
{
  if (pos == M)
  {
    for (const auto &num : vec)
    {
      std::cout << num << " ";
    }
    std::cout << "\n";
    return;
  }
  else if (prevNum == N + 1)
  {
    return;
  }

  vec.push_back(0);
  for (int i = prevNum; i <= N; ++i)
  {
    vec[pos] = i;
    DFS(vec, i, pos + 1);
  }
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::cin >> N >> M;
  DFS(std::vector<int>(), 1, 0);
}