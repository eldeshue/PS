// 병합 정렬 알고리즘 예제
// O(n log n)
// stable
// 추가적인 메모리 필요.
#include <iostream>
#include <vector>

int count;

void merge(std::vector<int> &V, int beg, int mid, int end) // end not included
{
  int l_length = mid - beg, r_length = end - mid;
  // set additional space
  std::vector<int> l_space(l_length + 1), r_space(r_length + 1);
  // copy
  for (int i = 0; i < l_length; ++i)
  {
    l_space[i] = V[beg + i];
  }
  for (int i = 0; i < r_length; ++i)
  {
    r_space[i] = V[mid + i];
  }
  // set sentinel, 2e9
  l_space[l_length] = r_space[r_length] = 2e9;
  // compare and wirte back
  int j = 0, k = 0;
  for (int i = 0; i < end - beg; ++i)
  {
    V[beg + i] = (r_space[k] >= l_space[j]) ? l_space[j++] : r_space[k++];
    count++;
  }
}

void mergeSort(std::vector<int> &V, int beg, int end) // endl not included
{
  // define exit condition
  if (beg + 1 >= end)
  {
    return;
  }

  // recurse to divide, call merge sort for left and right
  // get new mid value
  int mid = (end + beg) >> 1;
  mergeSort(V, beg, mid);
  mergeSort(V, mid, end);

  // call merge to conquer
  merge(V, beg, mid, end);
}

int main()
{
  int n;
  std::cin >> n;
  std::vector<int> data(n);
  for (auto &elem : data)
  {
    std::cin >> elem;
  }

  count = 0;

  mergeSort(data, 0, n);

  for (const auto &elem : data)
  {
    std::cout << elem << " ";
  }
  std::cout << "\n"
            << count << std::endl;
}