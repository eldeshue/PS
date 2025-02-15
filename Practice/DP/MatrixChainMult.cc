// 백준 11049번. 연속적 행렬 곱셈 최적화.
#include <iostream>

int N;                // num of matrix
int cache[500][500];  // cache[start][end] = mult count
int matrices[500][2]; // matrices[num][0] = row, [1] = colum

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::cin >> N;
  for (int i = 0; i < N; ++i)
  {
    std::cin >> matrices[i][0] >> matrices[i][1]; // row and colum
    cache[i][i] = 0;
  }

  // 대각선을 따라서 값을 계산해나감.
  // offset은 그 대각선이 주 대각선에서 얼마나 떨어져 있는지에 대한 offset임.
  for (int offset = 1; offset < N; ++offset)
  {
    for (int start = 0; start < N - offset; ++start) // 시작 행렬 결정.
    {
      int end = start + offset; // offset에 따라서 끝 행렬도 결정.
      int &tgt = cache[start][end] = 2e9;
      for (int pivot = start; pivot < end; ++pivot) // start와 end는 이미 결정된 값임.
      {                                             // pivot은 결합의 방법을 분할하기 위해서 설정한 기준임.
        tgt = std::min(tgt, cache[start][pivot] + cache[pivot + 1][end] +
                                matrices[start][0] * matrices[pivot][1] * matrices[end][1]);
      }
    }
  }

  std::cout << cache[0][N - 1]; // 목표로 하는 position.
}