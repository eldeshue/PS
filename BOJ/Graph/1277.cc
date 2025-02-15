
// Dijkstra
#include <iostream>
#include <cmath>
#include <queue>

typedef std::pair<int, int> point;

point locations[1001];
float graph[1001][1001];
float minDist[1001];

float calDist(const point &p1, const point &p2)
{
  float x = p1.first - p2.first;
  float y = p1.second - p2.second;
  return std::sqrt(x * x + y * y);
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int N, W;
  float M;
  std::cin >> N >> W >> M;
  for (int i = 1; i <= N; ++i)
  {
    std::cin >> locations[i].first >> locations[i].second;
  }
  ///////////
  for (int s = 1; s <= N; ++s)
  {
    // minDist[s] = 2e9;
    graph[s][s] = 2e9;
    for (int e = s + 1; e <= N; ++e)
    {
      graph[s][e] = calDist(locations[s], locations[e]);
      graph[e][s] = graph[s][e];
    }
  }
  //////////
  int a, b;
  for (int i = 0; i < W; ++i)
  {
    std::cin >> a >> b;
    graph[a][b] = 0;
    graph[b][a] = 0;
  }
  // Dijkstra
  for (int i = 1; i <= N; ++i)
  {
    minDist[i] = graph[1][i];
  }
  for (int mid = 2; mid <= N; ++mid)
  {
    for (int end = 1; end <= N; ++end)
    {
      float next = minDist[mid] + graph[mid][end];
      if (minDist[end] > next && mid != end)
      {
        minDist[end] = next;
      }
    }
  }
  std::cout << (int)(1000 * minDist[N]);
}