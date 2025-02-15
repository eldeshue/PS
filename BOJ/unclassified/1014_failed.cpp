#include <iostream>
#include <bitset>
#include <unordered_map>

int MAXROW, MAXCOLUM;
std::unordered_map<std::bitset<100>, int> cache;

void mask(std::bitset<100> &status, int row, int colum) // bitmasking
{
  int pos = row * MAXCOLUM + colum;
  status[pos] = true; // 0 is available place, so mask it to delete
}

void addPeople(std::bitset<100> &status, int row, int colum)
{
  int left = colum - 1;
  int right = colum + 1;
  int up = row - 1;
  int down = row + 1;

  if (right < MAXCOLUM)
  {
    mask(status, row, right);
    if (up >= 0)
    {
      mask(status, up, right);
    }
    if (down < MAXROW)
    {
      mask(status, down, right);
    }
  }
  if (left >= 0)
  {
    mask(status, row, left);
    if (up >= 0)
    {
      mask(status, up, left);
    }
    if (down < MAXROW)
    {
      mask(status, down, left);
    }
  }
  mask(status, row, colum);
}

bool isOK(std::bitset<100> status, int row, int colum)
{
  int pos = row * MAXCOLUM + colum;
  return !status.test(pos); // 0 means empty, available
}

int DP(std::bitset<100> status)
{
  if (cache.find(status) != cache.end()) // cache hit
  {
    return cache[status];
  }
  else
  {
    int result = -1;
    std::bitset<100> nextStatus;
    for (int r = 0; r < MAXROW; ++r)
    {
      for (int c = 0; c < MAXCOLUM; ++c) // M * N ....
      {
        if (isOK(status, r, c))
        {
          nextStatus = status;
          addPeople(nextStatus, r, c);
          result = std::max(result, DP(nextStatus));
        }
      }
    }
    cache.insert(std::make_pair(status, ++result));
    return result;
  }
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  char input;
  int testNum;
  std::bitset<100> status;
  std::cin >> testNum;
  for (int i = 0; i < testNum; ++i)
  {
    // setting initial status of the room
    cache.clear();
    status.set(false);
    std::cin >> MAXROW >> MAXCOLUM;
    for (int r = 0; r < MAXROW; ++r)
    {
      for (int c = 0; c < MAXCOLUM; ++c)
      {
        std::cin >> input;
        if (input == 'x') // if unavailable. 'x'
        {
          mask(status, r, c); // mask it. 1
        }
      }
    }
    // calculate max people
    std::cout << DP(status) << "\n";
  }
}