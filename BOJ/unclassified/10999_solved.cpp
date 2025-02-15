// lazy segment Tree
#include <iostream>
#include <vector>

template<typename T>
class LazySegmentTree
{
private:
	int size; 
	int treeSize;
	std::vector<T> a;		 
	std::vector<T> tree; 
	std::vector<T> lazy;	// save value for lazy propagation.

public:
	LazySegmentTree(int size) : size(size), treeSize(size * 4) 
	{
		a.resize(size + 1, 0);
		tree.resize(treeSize + 1, 0);
		lazy.resize(treeSize + 1, 0);
	};
	~LazySegmentTree() { a.clear(); tree.clear(); lazy.clear(); };

	void set(int index, T val);
	T get(int index);

	T init(int node, int start, int end);
	T query(int node, int start, int end, int left, int right);
	void updateLazy(int node, int start, int end);
	void updateRange(int node, int start, int end, int left, int right, T diff);
	void update(int index, T val);
};


int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, M, K;
	long long int a, b, c, d;
	std::cin >> N >> M >> K;
	LazySegmentTree<long long int> st(N);
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
			std::cin >> d;
			st.updateRange(1, 1, N, b, c, d);
		}
		else	// a == 2, query
		{
			std::cout << st.query(1, 1, N, b, c) << "\n";
		}
	}
}

template<typename T>
void LazySegmentTree<T>::set(int index, T val)
{
	a[index] = val;
}

template<typename T>
T LazySegmentTree<T>::get(int index)
{
	return a[index];
}

template<typename T>
T LazySegmentTree<T>::init(int node, int start, int end)
{
	if (start == end)
	{
		return tree[node] = a[start];
	}
	else
	{
		int mid = (start + end) >> 1;
		return tree[node] = this->init(node * 2, start, mid) + 
							this->init(node * 2 + 1, mid + 1, end);
	}
}

// update lazy vector
template<typename T>
void LazySegmentTree<T>::updateLazy(int node, int start, int end)
{
	if (lazy[node] != 0)	
	{
		// update
		tree[node] += (end - start + 1) * lazy[node];
		// propagate
		// only when it is needed
		if (start != end)
		{
			lazy[node * 2] += lazy[node];
			lazy[node * 2 + 1] += lazy[node];
		}
		// clear
		lazy[node] = 0;
	}
}

template<typename T>
void LazySegmentTree<T>::updateRange(int node, int start, int end, int left, int right, T diff)
{
	updateLazy(node, start, end);
	if (end < left || right < start)	// query out of range
	{
		return;
	}
	else if (left <= start && end <= right)	// in range, be lazy
	{
		tree[node] += (end - start + 1) * diff;
		if (start != end)	// not leaf
		{
			lazy[2 * node] += diff;
			lazy[2 * node + 1] += diff;
		}
		return;
	}
	else	// mixed, divide and conquer
	{
		int mid = (start + end) >> 1;
		this->updateRange(2 * node, start, mid, left, right, diff);
		this->updateRange(2 * node + 1, mid + 1, end, left, right, diff);
		tree[node] = tree[2 * node] + tree[2 * node + 1];
	}
}

template<typename T>
void LazySegmentTree<T>::update(int index, T val)
{
	T diff = val - a[index];
	a[index] = val;
	this->updateRange(1, 1, size, index, index, diff);
}

template<typename T>
T LazySegmentTree<T>::query(int node, int start, int end, int left, int right)
{
	updateLazy(node, start, end);
	if (left > end || right < start)	// out 
	{
		return 0;
	}
	else if (left <= start && end <= right)	// in
	{
		return tree[node];
	}
	else	// mix
	{
		int mid = (start + end) >> 1;
		return this->query(2 * node, start, mid, left, right)
			+ this->query(2 * node + 1, mid + 1, end, left, right);
	}
}



