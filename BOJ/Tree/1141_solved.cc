// BOJ, 1141
// 트리 구조의 포함 여부를 활용한 문제.
// 주어진 입력의 최대 양이 50개의 문자열이므로, 무식하게 풀어도 풀림.
#include <iostream>
#include <string>
#include <vector>

int N;
std::vector<std::string> buffer;
std::vector<int> tree[50];

bool isPrefix(const std::string &s, const std::string &l)
{
  int size = s.size();
  if (size == 0)
  {
    return true;
  }
  for (int i = 0; i < size; ++i)
  {
    if (s[i] != l[i])
    {
      return false;
    }
  }
  return true;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::cin >> N;
  buffer.resize(N);
  for (int i = 0; i < N; ++i)
  {
    std::cin >> buffer[i];
  }

  // build tree.
  for (int i = 0; i < N - 1; ++i)
  {
    for (int j = i + 1; j < N; ++j) // O(N ^ 2)
    {
      if (buffer[i].size() > buffer[j].size())
      {
        std::string &s_str = buffer[j];
        std::string &l_str = buffer[i];
        if (isPrefix(s_str, l_str))
        {
          tree[j].push_back(i);
        }
      }
      else
      {
        std::string &s_str = buffer[i];
        std::string &l_str = buffer[j];
        if (isPrefix(s_str, l_str))
        {
          tree[i].push_back(j);
        }
      }
    }
  }

  // calculate result
  int result = 0;
  for (int i = 0; i < N; ++i)
  {
    if (tree[i].size() == 0)
      result++;
  }
  std::cout << result;
}