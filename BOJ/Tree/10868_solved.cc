// 범위 기반의 최소값
// 기본 세그먼트 트리.
#include <iostream>
#include <vector>

template <typename T>
class SegmentTree
{
private:
  int size; // index starts from 1
  int treeSize;
  std::vector<T> a;
  std::vector<T> tree;

public:
  SegmentTree(int size) : size(size), treeSize(size * 4)
  {
    a.resize(size + 1);
    tree.resize(treeSize + 5);
  }
  ~SegmentTree()
  {
    a.clear();
    tree.clear();
  }

  void set(int index, T val);
  T get(int index);

  T init(int start, int end, int node);
  T query(int start, int end, int node, int left, int right);
};

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int N, M, a, b, temp;
  std::cin >> N >> M;
  SegmentTree<int> st(N);
  for (int i = 1; i <= N; ++i)
  {
    std::cin >> temp;
    st.set(i, temp);
  }
  st.init(1, N, 1);
  for (int i = 0; i < M; ++i)
  {
    std::cin >> a >> b;
    std::cout << st.query(1, N, 1, a, b) << "\n";
  }
}

template <typename T>
void SegmentTree<T>::set(int index, T val)
{
  if (index >= 1 && index <= size)
  {
    a[index] = val;
  }
}

template <typename T>
T SegmentTree<T>::get(int index)
{
  if (index >= 1 && index <= size)
  {
    return a[index];
  }
}
template <typename T>
T SegmentTree<T>::init(int start, int end, int node)
{
  if (start == end) // base case
  {
    return tree[node] = a[start];
  }
  else
  {
    int mid = (start + end) >> 1;
    T leftVal = this->init(start, mid, node * 2);
    T rightVal = this->init(mid + 1, end, node * 2 + 1);
    return tree[node] = ((leftVal < rightVal) ? leftVal : rightVal);
  }
}

template <typename T>
T SegmentTree<T>::query(int start, int end, int node, int left, int right)
{
  // out of range, ���ص� ������.
  if (left > end || right < start)
  {
    return 2e9;
  }
  else if (left <= start && end <= right) // in range, ��ȯ
  {
    return tree[node];
  }
  else // ������ �ɸ��� ���, ���� �ʿ�
  {
    int mid = (start + end) >> 1;
    T leftVal = this->query(start, mid, node * 2, left, right);
    T rightVal = this->query(mid + 1, end, node * 2 + 1, left, right);
    return ((leftVal < rightVal) ? leftVal : rightVal);
  }
}