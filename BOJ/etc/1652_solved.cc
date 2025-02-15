
#include <iostream>

int N;
typedef struct room
{
  bool space[100][100];
} room;

int cntRowSpace(room r)
{
  int result = 0;
  for (int row = 0; row < N; ++row)
  {
    for (int col = 0; col < N - 1; ++col)
    {
      if (r.space[row][col] == true)
      {
        r.space[row][col] = false;
        if (r.space[row][col + 1] == true)
        {
          result++;
          int d = col + 1;
          while (r.space[row][d] == true && d < N)
          {
            r.space[row][d] = true;
            d++;
          }
          col = d;
        }
      }
    }
  }
  return result;
}

int cntColSpace(room r)
{
  int result = 0;
  for (int col = 0; col < N; ++col)
  {
    for (int row = 0; row < N - 1; ++row)
    {
      if (r.space[row][col] == true)
      {
        r.space[row][col] == false;
        if (r.space[row + 1][col] == true)
        {
          result++;
          int d = row + 1;
          while (r.space[d][col] == true && d < N)
          {
            r.space[d][col] = false;
            d++;
          }
          row = d;
        }
      }
    }
  }
  return result;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  char status;
  room R;
  std::cin >> N;
  for (int r = 0; r < N; ++r)
  {
    for (int c = 0; c < N; ++c)
    {
      std::cin >> status;
      if (status == '.')
      {
        R.space[r][c] = true;
      }
      else
      {
        R.space[r][c] = false;
      }
    }
  }
  std::cout << cntRowSpace(R) << " " << cntColSpace(R);
}