#include <iostream>

int partition(int *arr, int beg_index, int end_index) // end not included
{
  int next_swap = beg_index;
  int standard = arr[end_index - 1];
  for (int i = beg_index; i < end_index; ++i)
  {
    if (arr[i] > standard)
    {
      continue;
    }
    else // arr[i] <= standard, swap needed
    {
      // swap
      int temp = arr[i];
      arr[i] = arr[next_swap];
      arr[next_swap] = temp;

      next_swap++;
    }
  }

  return next_swap; // return latest swap index
}

void QuickSort(int *arr, int beg, int end) // end not included
{
  if (beg >= end)
  {
    return;
  }
  // divide
  int new_beg = partition(arr, beg, end);

  // conquer
  QuickSort(arr, beg, new_beg - 1); // 기존의 기준값은 무시함(즉 다음 정렬에서 재외함)
  QuickSort(arr, new_beg, end);
}

int main()
{
  int n = 12;
  // std::cin >> n;
  //  int *array = new int[n];
  int array[12] = {4, 62, 11, 2, 654, 1, 51, 3, 12, 5, 34, 35};

  /*
    for (int i = 0; i < n; ++i)
    {
      std::cin >> array[i];
    }
    */

  QuickSort(array, 0, n);

  for (int i = 0; i < n; ++i)
  {
    std::cout << array[i] << " ";
  }

  // delete[] array;
}