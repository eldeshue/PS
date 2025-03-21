
#include <iostream>
#include <vector>

// integer summation segmentent tree
/*
	using heap tree
	all access to the seg tree will be zero indexed
 */
class IntSumSegTree
{
private:
	int IE = 0;
	const int depth;
	const int offset;
	const int sizeTree;
	std::vector<int> tree;

	static int log2(int n)
	{
		int result = 0;
		while ((1 << result) < n)
			result++;
		return result;
	}
public:
	IntSumSegTree(int num) : depth(log2(num) + 1), offset(1 << (depth - 1)), sizeTree(1 << depth), tree(sizeTree, IE) {};
	void setLeaf(int idx, int val) {tree[offset + idx] = val;};
	void initTree();
	void pointUpdate(int idx, int val);
	int pointQuery(int idx) const {return tree[ + idx];};
	int rangeQuery(int l, int r) const;
};

void IntSumSegTree::initTree()	// not using
{
	for (int idx = sizeTree - 1; idx > 1; --idx)
	{
		tree[idx >> 1] += tree[idx];
	}
}

void IntSumSegTree::pointUpdate(int idx, int val)
{
	const int diff = val - tree[offset + idx];
	for (int pos = offset + idx; pos > 0; pos >>= 1)
	{
		tree[pos] += diff;
	}
}

int IntSumSegTree::rangeQuery(int l, int r) const
{
	int lSum = IE, rSum = IE;
	if (l > r)
		std::swap(l, r);	// l <= r, must
	l += offset;
	r += offset;
	//
	while (l <= r)
	{
		// left sum
		if (l & 1)	// odd
		{
			lSum += tree[l];
			l++;
		}
		// right sum
		if (~r & 1)	// even
		{
			rSum += tree[r];
			r--;
		}
		l >>= 1;
		r >>= 1;
	}
	//
	return lSum + rSum;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int nodeNum, queryNum, i, j, k;
	std::cin >> nodeNum >> queryNum;
	IntSumSegTree st(nodeNum);
	// dont need to set value and init tree
	for (int q = 0; q < queryNum; ++q)
	{
		std::cin >> i >> j >> k;
		if (i)	// update
		{
			st.pointUpdate(j - 1, k);
		}
		else 	// query
		{
			std::cout << st.rangeQuery(j - 1, k - 1) << '\n';
		}
	}
}
