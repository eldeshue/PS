
#include <iostream>
#include <memory.h>
#include <vector>

int board[10][10];
std::vector<std::pair<int, int>> emptyPoints;

void check_row(int cur_row, bool *buffer)
{
  for (int x = 1; x < 10; ++x)
  {
    if (board[cur_row][x] != 0)
    {
      buffer[board[cur_row][x]] = true;
    }
  }
}

void check_col(int cur_col, bool *buffer)
{
  for (int y = 1; y < 10; ++y)
  {
    if (board[y][cur_col] != 0)
    {
      buffer[board[y][cur_col]] = true;
    }
  }
}

void check_block(int cur_row, int cur_col, bool *buffer)
{
  int start_y = cur_row / 3 * 3 + 1;
  int start_x = cur_col / 3 * 3 + 1;
  for (int y = start_y; y < start_y + 3; ++y)
  {
    for (int x = start_x; x < start_x + 3; ++x)
    {
      if (board[y][x] != 0)
      {
        buffer[board[y][x]] = true;
      }
    }
  }
}

void DFS(int cur_index)
{
  if (cur_index == emptyPoints.size())
  {
    for (int i = 1; i < 10; ++i)
    {
      for (int j = 1; j < 10; ++j)
      {
        std::cout << board[i][j];
      }
      std::cout << "\n";
    }
    return;
  }
  bool is_filled[10];
  int cur_y = emptyPoints[cur_index].first;
  int cur_x = emptyPoints[cur_index].second;
  check_block(cur_y, cur_x, is_filled);
  check_row(cur_y, is_filled);
  check_col(cur_x, is_filled);
  for (int i = 1; i < 10; ++i)
  {
    if (!is_filled[i])
    {
      board[cur_y][cur_x] = i;
      DFS(cur_index + 1);
      board[cur_y][cur_x] = 0;
    }
  }
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  for (int i = 1; i < 10; ++i)
  {
    for (int j = 1; j < 10; ++j)
    {
      std::cin >> board[i][j];
      if (board[i][j] == 0)
      {
        emptyPoints.push_back(std::make_pair(i, j));
      }
    }
  }
  DFS(0);
}