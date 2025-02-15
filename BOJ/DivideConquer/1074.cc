// Z
// solved
#include <iostream>

int calZ(int row, int colum, int level)
{
  if (level == 0)
  {
    return 0;
  }

  // 위치하는 4분면 찾기
  int devider = 1 << (level - 1);

  bool row_flag = (row >= devider);
  bool col_flag = (colum >= devider);
  if (row_flag != true && col_flag != true)
  {
    return calZ(row, colum, level - 1);
  }
  else if (row_flag != true && col_flag == true)
  {
    return devider * devider + calZ(row, colum - devider, level - 1);
  }
  else if (row_flag == true && col_flag != true)
  {
    return 2 * devider * devider + calZ(row - devider, colum, level - 1);
  }
  else
  {
    return 3 * devider * devider + calZ(row - devider, colum - devider, level - 1);
  }
}

int main()
{
  int n, r, c;
  std::cin >> n >> r >> c; // n, row, colum
  // test
  // n = 2, r = 3, c = 1;

  std::cout << calZ(r, c, n);
}