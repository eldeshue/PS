
#include <iostream>
#include <vector>

int N, M;

void DFS(std::vector<int> vec, int statusBit, int prevNum, int pos)
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
  else if (prevNum == N)
  {
    return;
  }

  vec.push_back(0);
  for (int i = prevNum + 1; i <= N; ++i)
  {
    if ((statusBit & (1 << i)) == 0)
    {
      vec[pos] = i;
      DFS(vec, statusBit | (1 << i), i, pos + 1);
    }
  }
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::cin >> N >> M;
  DFS(std::vector<int>(), 0, 0, 0);
}
