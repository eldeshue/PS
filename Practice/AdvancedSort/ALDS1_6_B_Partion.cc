
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

  return next_swap - 1; // return latest swap index
}

int main()
{
  int n;
  std::cin >> n;
  int *array = new int[n];
  for (int i = 0; i < n; ++i)
  {
    std::cin >> array[i];
  }
  /*
  // test
  int n = 12;
  int array[12] = {13, 19, 9, 5, 12, 8, 7, 4, 21, 2, 6, 11};
  */
  int tgt = partition(array, 0, n);

  for (int i = 0; i < n; ++i)
  {
    if (i == tgt)
    {
      std::cout << "[" << array[i] << "] ";
    }
    else
    {
      std::cout << array[i] << " ";
    }
  }

  delete[] array;
}