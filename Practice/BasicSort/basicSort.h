// functions that implement basic sorting algorithm
#include <vector>

template <typename T>
void insertionSort_up(T *array, int length)
{
  for (int i = 1; i < length; i++)
  {
    T target = array[i];
    int sortedIndex = i - 1;
    while (sortedIndex >= 0 && target < array[sortedIndex])
    {
      // push backward
      array[sortedIndex + 1] = array[sortedIndex];
      sortedIndex--;
    }
    // else, insert
    array[sortedIndex + 1] = target;
  }
}

template <typename T>
void insertionSort_down(T *array, int length)
{
  for (int i = 1; i < length; i++)
  {
    T target = array[i];
    int sortedIndex = i - 1;
    while (sortedIndex >= 0 && target > array[sortedIndex])
    {
      array[sortedIndex + 1] = array[sortedIndex];
      sortedIndex--;
    }
    array[sortedIndex + 1] = target;
  }
}

template <typename T>
void bubbleSort_up(T *array, int length)
{
  bool flag = true;
  while (flag)
  {
    flag = 0;
    for (int i = 0; i < length - 1; i++)
    {
      if (array[i + 1] < array[i])
      {
        // swap
        T temp = array[i];
        array[i] = array[i + 1];
        array[i + 1] = temp;
        // flag on
        flag = 1;
      }
    }
  }
}

template <typename T>
void bubbleSort_down(T *array, int length)
{
  bool flag = true;
  while (flag)
  {
    flag = 0;
    for (int i = 0; i < length - 1; i++)
    {
      if (array[i] < array[i + 1])
      {
        T temp = array[i];
        array[i] = array[i + 1];
        array[i + 1] = temp;
        flag = 1;
      }
    }
  }
}

template <typename T> // T is usually a number.
void selectionSort_up(T *array, int length)
{
  T temp_element;
  int target_index;
  for (int i = 0; i < length - 1; i++)
  {
    temp_element = array[i];
    target_index = i;
    for (int j = i + 1; j < length; j++)
    {
      // find the smallest element among unsorted area.
      if (temp_element > array[j])
      {
        temp_element = array[j]; // update the value
        target_index = j;        // index of the potential smallest element
      }
    }
    // swap the element.
    array[target_index] = array[i];
    array[i] = temp_element;
  }
}

template <typename T> // T is usually a number.
void selectionSort_down(T *array, int length)
{
  T temp_element;
  int target_index;
  for (int i = 0; i < length - 1; i++)
  {
    temp_element = array[i];
    target_index = i;
    for (int j = i + 1; j < length; j++)
    {
      // find the largest element among unsorted area.
      if (temp_element < array[j])
      {
        temp_element = array[j]; // update the value
        target_index = j;        // index of the potential largest element
      }
    }
    // swap the element.
    array[target_index] = array[i];
    array[i] = temp_element;
  }
}

/*
 * shell's sort
 * 주어진 배열을 특정 기준으로 나눈 후 삽입 정렬을 반복하는 알고리즘
 * 배열을 나누는 기준이 되는 값인 G의 선정이 효율을 결정함
 * 현재 사용된 G값 선정 알고리즘은 g_n = 3 * g_n-1 + 1
 */
const std::vector<int> &get_G(int n)
{
  // static 으로 선언하여 자원 공간 한정 및 scope로 접근 제한
  static std::vector<int> G;
  if (G.empty())
  {
    G.push_back(1);
  }

  int temp;
  while ((temp = G.back()) < n)
  {
    G.push_back(3 * temp + 1);
  }

  return G;
}
template <typename T>
void shellSort_up(T *array, int length)
{
  const std::vector<int> &g = get_G(length);

  int index_MaxG = 0;
  try
  {
    while (g.at(index_MaxG) < length)
    {
      index_MaxG++;
    }
    index_MaxG--;
  }
  catch (std::out_of_range &e)
  {
    index_MaxG = g.size() - 1;
  }

  for (int i = index_MaxG; i >= 0; i--) // i는 현재 gap의 index
  {
    int gap = g.at(i);
    for (int j = gap; j < length; j++) // j는 array의 시작 target index
    {
      int target_index = j;
      int comp_index = j - gap;
      while (comp_index >= 0) // 분할된 부분에 대한 정렬
      {
        T target_value = array[target_index];
        T comp_value = array[comp_index];
        if (target_value < comp_value) // 오름차순이 아닌 경우
        {
          // swap
          array[target_index] = comp_value;
          array[comp_index] = target_value;

          target_index = comp_index;
        }
        comp_index -= gap;
      }
    }
  }
}

template <typename T>
void shellSort_down(T *array, int length)
{
  const std::vector<int> &g = get_G(length);

  int index_MaxG = 0;
  try
  {
    while (g.at(index_MaxG) < length)
    {
      index_MaxG++;
    }
    index_MaxG--;
  }
  catch (std::out_of_range &e)
  {
    index_MaxG = g.size() - 1;
  }

  for (int i = index_MaxG; i >= 0; i--) // i는 현재 gap의 index
  {
    int gap = g.at(i);
    for (int j = gap; j < length; j++) // j는 array의 시작 target index
    {
      int target_index = j;
      int comp_index = j - gap;
      while (comp_index >= 0) // 분할된 부분에 대한 정렬
      {
        T target_value = array[target_index];
        T comp_value = array[comp_index];
        if (target_value > comp_value) // 내림차순이 아닌 경우
        {
          // swap
          array[target_index] = comp_value;
          array[comp_index] = target_value;

          target_index = comp_index;
        }
        comp_index -= gap;
      }
    }
  }
}