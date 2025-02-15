#include <iostream>
#include <set>
#include <vector>
#include <queue> // priority queue
#define INF 2e9
int length, N, minS, maxS;
std::set<int> S;

int calNumArea(int start, int end, int tgt) // both end included
{
  return (tgt - start + 1) * (end - tgt + 1);
}

int calNumGoodArea(int includeNum)
{
  // if included
  if (S.find(includeNum) != S.end())
  {
    return 0;
  }
  // not included
  if (includeNum < minS) // left
  {
    return calNumArea(1, minS - 1, includeNum);
  }
  else if (maxS < includeNum) // right
  {
    return INF;
  }
  else // middle
  {
    // find nearest range
    int s = includeNum - 1;
    int e = includeNum + 1;
    while (S.find(s) == S.end())
    {
      s--;
    }
    while (S.find(e) == S.end())
    {
      e++;
    }
    return calNumArea(s + 1, e - 1, includeNum);
  }
}

struct compare
{
  bool operator()(std::pair<int, int> &pair1, std::pair<int, int> &pair2)
  {
    if (pair1.second == pair2.second || (pair1.second == INF && pair2.second == INF))
    {
      return pair1.first > pair2.first;
    }
    else
    {
      return pair1.second > pair2.second;
    }
  }
};

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, compare> PQ;

  // initialize set S
  int input;
  std::cin >> length;
  for (int i = 0; i < length; ++i)
  {
    std::cin >> input;
    S.insert(input);
  }
  minS = *(S.begin());
  maxS = *(S.rbegin());
  // calculate and put them in the PQ
  std::cin >> N;
  int count = 0;
  int pos1 = 1, pos2 = minS - 1;
  for (const auto &pos : S)
  {
    PQ.push(std::make_pair(pos, calNumGoodArea(pos)));
    count++;
  }
  for (int i = minS + 1; i < maxS; ++i)
  {
    if (S.find(i) == S.end())
    {
      PQ.push(std::make_pair(i, calNumGoodArea(i)));
      count++;
    }
  }
  while (count <= N)
  {
    PQ.push(std::make_pair(pos1, calNumGoodArea(pos1)));
    PQ.push(std::make_pair(pos2, calNumGoodArea(pos2)));
    count += 2;
    pos1++;
    pos2--;
  }
  // print in order
  for (int i = 0; i < N; ++i)
  {
    std::cout << PQ.top().first << " ";
    PQ.pop();
  }
}