
#include <iostream>
#include <memory.h>

int N;
bool graph[100][100];

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  memset(graph, 0, sizeof(graph));

  std::cin >> N;
  for (int i = 0; i < N; ++i)
  {
    for (int j = 0; j < N; ++j)
    {
      std::cin >> graph[i][j];
    }
  }

  // floyd - warshall
  for (int m = 0; m < N; ++m)
  {
    for (int s = 0; s < N; ++s)
    {
      for (int e = 0; e < N; ++e)
      {
        if (graph[s][m] && graph[m][e])
        {
          graph[s][e] = true;
        }
      }
    }
  }

  for (int i = 0; i < N; ++i)
  {
    for (int j = 0; j < N; ++j)
    {
      std::cout << graph[i][j] << " ";
    }
    std::cout << "\n";
  }
}