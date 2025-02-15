// solved, but little bit slow.
#include <iostream>

int pos_num, zero_num, neg_num;

bool ok(int **paper, int start_row, int start_col, int n)
{
  int standard = paper[start_row][start_col];
  for (int i = 0; i < n; ++i)
  {
    for (int j = 0; j < n; ++j)
    {
      if (paper[start_row + i][start_col + j] != standard)
        return false;
    }
  }
  return true;
}

void divideOrNot(int **paper, int start_row, int start_col, int n)
{
  if (n == 0)
  {
    return;
  }

  if (ok(paper, start_row, start_col, n))
  {
    switch (paper[start_row][start_col])
    {
    case 1:
      pos_num++;
      return;
      break;
    case 0:
      zero_num++;
      return;
      break;
    case -1:
      neg_num++;
      return;
      break;
    default:
      break;
    }
  }
  else
  { // divide
    int new_n = n / 3;
    divideOrNot(paper, start_row, start_col, new_n);
    divideOrNot(paper, start_row, start_col + new_n, new_n);
    divideOrNot(paper, start_row, start_col + 2 * new_n, new_n);
    divideOrNot(paper, start_row + new_n, start_col, new_n);
    divideOrNot(paper, start_row + new_n, start_col + new_n, new_n);
    divideOrNot(paper, start_row + new_n, start_col + 2 * new_n, new_n);
    divideOrNot(paper, start_row + 2 * new_n, start_col, new_n);
    divideOrNot(paper, start_row + 2 * new_n, start_col + new_n, new_n);
    divideOrNot(paper, start_row + 2 * new_n, start_col + 2 * new_n, new_n);
  }
}

int main()
{
  pos_num = zero_num = neg_num = 0;

  int N;
  std::cin >> N;

  int **paper = new int *[N];
  for (int i = 0; i < N; ++i)
  {
    paper[i] = new int[N];
  }

  for (int i = 0; i < N; ++i)
  {
    for (int j = 0; j < N; ++j)
    {
      std::cin >> paper[i][j];
    }
  }

  // processing
  divideOrNot(paper, 0, 0, N);

  // output
  std::cout << neg_num << "\n"
            << zero_num << "\n"
            << pos_num << std::endl;

  for (int i = 0; i < N; ++i)
  {
    delete[] paper[i];
  }
  delete[] paper;
}