
/*
	seg tree 응용문제

	두 종류의 query를 처리하는 세그트리문제임.
	하나는 포인트 업데이트 쿼리(A == 2). -> 전통적인 세그트리 방식.

	다른 하나는 범위 쿼리(A == 1), 주어진 등수에 해당하는 맛을 찾아야 함.
		-> 등수라는 것은 누적 합임. 0번 taste부터 시작함.
		-> 즉 [0, n]의 누적합들 중, 처음으로 등수(rank)를 넘는 누적합을 만드는 n을 찾는 문제임.
		-> 즉 쿼리에 대해서 2진 탐색을 수행해야 하는 부분....
		-> parametric search (log n) * each_query(log n) = O((log n) ^ 2)
*/
#include <iostream>
#include <vector>

// segtree class
template <typename NodeType, typename F_Merge>
struct SegTree
{ // 1-indexed
public:
	using A = NodeType;
	SegTree() : SegTree(0, A()) {}
	explicit SegTree(int n, const A &e) : n(n), lg(Log2(n)), sz(1 << lg), e(e), tree(sz << 1, e) {}
	void Set(int i, const A &val) { tree[--i | sz] = val; }
	void Init()
	{
		for (int i = sz - 1; i; i--)
			tree[i] = M(tree[i << 1], tree[i << 1 | 1]);
	}
	void Update(int i, const A &val)
	{
		tree[--i |= sz] = val; // leaf
		while (i >>= 1)
			tree[i] = M(tree[i << 1], tree[i << 1 | 1]); // merge, climb up
	}
	A Query(int i) const { return tree[--i | sz]; }
	A Query(int l, int r) const
	{
		A L = e, R = e;
		for (--l |= sz, --r |= sz; l <= r; l >>= 1, r >>= 1)
		{
			if (l & 1)
				L = M(L, tree[l++]); // if l is odd
			if (~r & 1)
				R = M(tree[r--], R); // if r is even
		}
		return M(L, R);
	}

private:
	const int n, lg, sz;
	const A e;
	std::vector<A> tree;
	F_Merge M;
	static int Log2(int n)
	{
		int ret = 0;
		while (n > 1 << ret)
			ret++;
		return ret;
	} // up scale
};

struct F_Merge
{
	long long operator()(const long long &n1, const long long &n2) const
	{
		return n1 + n2;
	}
};

// parametric search
int findTaste(const SegTree<long long, F_Merge> &sg, int rank)
{
	int low = 1, high = 1000000;

	while (low != high)
	{
		int mid = (low + high) >> 1;
		if (sg.Query(1, mid) >= rank)
		{
			high = mid;
		}
		else
		{
			low = mid + 1;
		}
	}
	return low;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	/*
		N : number of query
		A : type of query, 1(range data query from 0), 2(point update query)
		B : info of query,
			if A == 1, B is ranking of taste.
			if A == 2, B is num of taste
		C : info of quert,
			if A == 1, nothing, do not use.
			if A == 2, number of data to update
	*/
	// set seg tree
	SegTree<long long, F_Merge> sg(1000000, 0);
	// skip Init, seg tree is empty at start point.

	// get input
	int N, A, B, C;
	std::cin >> N;
	while (N--)
	{
		std::cin >> A;
		if (A == 1) // range query, find taste according to the rank
		{
			std::cin >> B;
			// parametric search
			int taste = findTaste(sg, B);
			// update
			sg.Update(taste, sg.Query(taste) - 1);
			// print value
			std::cout << taste << '\n';
		}
		else // simply update seg tree
		{
			std::cin >> B >> C;
			sg.Update(B, sg.Query(B) + C);
		}
	}
}
