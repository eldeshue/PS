
#include <iostream>
#include <queue>
#include <deque>

int N, M;
std::deque<int> roundDQ;
std::queue<int> next;
int cnt = 0;

void movLeft()
{
  roundDQ.push_back(roundDQ.front());
  roundDQ.pop_front();
  cnt++;
}
void movRight()
{
  roundDQ.push_front(roundDQ.back());
  roundDQ.pop_back();
  cnt++;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int input;
  std::cin >> N >> M;
  for (int i = 1; i <= N; ++i)
  {
    roundDQ.push_back(i);
  }
  for (int i = 0; i < M; ++i)
  {
    std::cin >> input;
    next.push(input);
  }
  //
  while (!next.empty())
  {
    int curPos = roundDQ.front();
    int tgt = next.front();
    int step = 0;
    for (auto itr = roundDQ.begin(); itr != roundDQ.end(); ++itr)
    {
      if (*itr == tgt)
      {
        break;
      }
      step++;
    }
    step = ((N - step) < step) ? (step - N) : step;

    if (step >= 0)
    {
      for (int i = 0; i < step; ++i)
      {
        movLeft();
      }
    }
    else // step < 0
    {
      for (int i = step; i < 0; ++i)
      {
        movRight();
      }
    }
    N--;
    roundDQ.pop_front();
    next.pop();
  }

  std::cout << cnt;
}