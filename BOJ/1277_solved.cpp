#include <iostream>
#include <cmath>
#include <vector>
#include <queue>

typedef std::pair<int, int> point;
typedef std::pair<int, double> node;

struct comp
{
    bool operator()(const node& n1, const node& n2)
    {
        return n1.second > n2.second;
    }
};

int N, W;
point locations[1001];
double graph[1001][1001];
double minDist[1001];

void Dijkstra()
{
    std::priority_queue<node, std::vector<node>, comp> PQ;

    PQ.push(std::make_pair(1, 0));
    minDist[1] = 0;
    while (!PQ.empty())
    {
        int curNode = PQ.top().first;
        double curCost = PQ.top().second;
        PQ.pop();
        if (minDist[curNode] < curCost)
        {
            continue;
        }

        for (int nextNode = 1; nextNode <= N; ++nextNode)
        {
            double nextVal = minDist[curNode] + graph[curNode][nextNode];
            if (minDist[nextNode] > nextVal)
            {
                minDist[nextNode] = nextVal;
                PQ.push(std::make_pair(nextNode, nextVal));
            }
        }
    }
}

double calDist(const point &p1, const point &p2)
{
  double x = p1.first - p2.first;
  double y = p1.second - p2.second;
  return std::sqrt(x * x + y * y);
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  double M;
  std::cin >> N >> W >> M;
  for (int i = 1; i <= N; ++i)
  {
    std::cin >> locations[i].first >> locations[i].second;
  }
  ///////////
  // 그래프 초기화
  for (int s = 1; s <= N; ++s)
  {
      minDist[s] = 3e38;
    graph[s][s] = 3e38;
    for (int e = s + 1; e <= N; ++e)
    {
        double dist = calDist(locations[s], locations[e]);
        if (dist <= M)
        {
            graph[s][e] = dist;
        }
        else
        {
            graph[s][e] = 3e38;
        }
           graph[e][s] = graph[s][e];
    }
  }
  //////////
  // 이미 연결된 발전소
  int a, b;
  for (int i = 0; i < W; ++i)
  {
    std::cin >> a >> b;
    graph[a][b] = 0;
    graph[b][a] = 0;
  }
  // Dijkstra
  Dijkstra();

   std::cout << (long long)(1000 * minDist[N]);
}