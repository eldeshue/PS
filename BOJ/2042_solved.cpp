// segment Tree
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
		tree.resize(treeSize + 4);
	}
	~SegmentTree()
	{
		a.clear();
		tree.clear();
	}

	void set(int index, T val);
	T get(int index);

	T init(int node, int start, int end);
	T query(int node, int start, int end, int left, int right);
	void updateDiff(int node, int start, int end, int index, T dif);
	void update(int index, T val);
};

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, M, K;
	long long int a, b, c;
	std::cin >> N >> M >> K;
	SegmentTree<long long int> st(N);
	for (int i = 1; i <= N; ++i)
	{
		std::cin >> a;
		st.set(i, a);
	}
	st.init(1, 1, N);
	for (int i = 0; i < M + K; ++i)
	{
		std::cin >> a >> b >> c;
		if (a == 1)	// update
		{
			st.update(b, c);
		}
		else	// a == 2, query
		{
			std::cout << st.query(1, 1, N, b, c) << "\n";
		}
	}
}

template <typename T>
void SegmentTree<T>::set(int index, T val)
{
	a[index] = val;
}

template <typename T>
T SegmentTree<T>::get(int index)
{
	return a[index];
}

template <typename T>
T SegmentTree<T>::init(int node, int start, int end)
{
	if (start == end) 
	{
		return tree[node] = a[start];
	}
	else 
	{
		int mid = (start + end) >> 1;
		return tree[node] = this->init(node * 2, start, mid)					
						+ this->init(node * 2 + 1, mid + 1, end); 
	}
}

template <typename T>
T SegmentTree<T>::query(int node, int start, int end, int left, int right)
{
	if (left > end || right < start)
	{
		return 0;
	}
	else if (left <= start && end <= right) 
	{
		return tree[node];
	}
	else
	{
		int mid = (start + end) >> 1;
		return this->query(node * 2, start, mid, left, right) 
			+ this->query(node * 2 + 1, mid + 1, end, left, right);
	}
}

template <typename T>
void SegmentTree<T>::updateDiff(int node, int start, int end, int index, T dif)
{
	if (index < start || index > end)
	{
		return;
	}
	else
	{
		tree[node] += dif;
		if (start == end)
			return;
		int mid = (start + end) >> 1;
		this->updateDiff(node * 2, start, mid, index, dif);
		this->updateDiff(node * 2 + 1, mid + 1, end, index, dif);
	}
}

template <typename T>
void SegmentTree<T>::update(int index, T val)
{
	T diff = val - a[index];
	a[index] = val;
	this->updateDiff(1, 1, size, index, diff);
}



