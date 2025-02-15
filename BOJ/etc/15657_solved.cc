#include <iostream>
#include <algorithm>
#include <vector>

int N, M;
std::vector<int> nums;

void DFS(std::vector<int> vec, int prevIndex, int pos)
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
  else if (prevIndex == N)
  {
    return;
  }

  vec.push_back(0);
  for (int i = prevIndex; i < N; ++i)
  {
    vec[pos] = nums[i];
    DFS(vec, i, pos + 1);
  }
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::cin >> N >> M;
  nums.resize(N);
  for (int i = 0; i < N; ++i)
  {
    std::cin >> nums[i];
  }
  std::sort(nums.begin(), nums.end());
  DFS(std::vector<int>(), 0, 0);
}