
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <unordered_map>

template <typename NodeType,
		  typename LazyType,
		  typename F_Merge,
		  typename F_Update,
		  typename F_Composition>
struct LazySegTree
{ // 1-indexed
public:
	using A = NodeType;
	using B = LazyType;
	LazySegTree() : LazySegTree(0, A(), B()) {}
	explicit LazySegTree(int n, const A &e, const B &id)
		: n(n), e(e), id(id), lg(Log2(n)), sz(1 << lg), tree(sz << 1, e), lazy(sz, id) {}
	void Set(int i, const A &val) { tree[--i | sz] = val; }
	void Init()
	{
		for (int i = sz - 1; i; i--)
			Pull(i);
	}
	void Update(int i, const B &f)
	{
		--i |= sz;
		for (int j = lg; j; j--)
			Push(i >> j); // propagate prev lazy.
		Apply(i, f);
		for (int j = 1; j <= lg; j++)
			Pull(i >> j);
	}
	void Update(int l, int r, const B &f)
	{ /// range update
		--l |= sz, --r |= sz;
		// top to bottom, propagate previously setted lazy value
		for (int i = lg; i; i--)
		{
			if (l >> i << i != l)
				Push(l >> i);
			if (r + 1 >> i << i != r + 1)
				Push(r >> i);
		}
		// set new lazy value
		for (int L = l, R = r; L <= R; L >>= 1, R >>= 1)
		{
			if (L & 1)
				Apply(L++, f);
			if (~R & 1)
				Apply(R--, f);
		}
		// bottom to top, update parent
		for (int i = 1; i <= lg; i++)
		{
			if (l >> i << i != l)
				Pull(l >> i);
			if (r + 1 >> i << i != r + 1)
				Pull(r >> i);
		}
	}
	A Query(int i)
	{ // point query
		--i |= sz;
		for (int j = lg; j; j--)
			Push(i >> j); // propagate lazy
		return tree[i];
	}
	A Query(int l, int r)
	{ // range query
		A L = e, R = e;
		--l |= sz, --r |= sz;
		for (int i = lg; i; i--)
		{ // propagate lazy value
			if (l >> i << i != l)
				Push(l >> i); // to lazy propagate, get leaf of lazy tree
			if (r + 1 >> i << i != r + 1)
				Push(r >> i);
		}
		for (; l <= r; l >>= 1, r >>= 1)
		{ // query
			if (l & 1)
				L = M(L, tree[l++]);
			if (~r & 1)
				R = M(tree[r--], R);
		}
		return M(L, R);
	}

private:
	const int n, lg, sz;
	const A e;
	const B id;
	std::vector<A> tree;
	std::vector<B> lazy;
	F_Merge M;
	F_Update U;
	F_Composition C;
	static int Log2(int n)
	{
		int ret = 0;
		while (n > 1 << ret)
			ret++;
		return ret;
	}
	void Apply(int i, const B &f)
	{ // update and set lazy value
		tree[i] = U(f, tree[i]);
		if (i < sz)
			lazy[i] = C(f, lazy[i]);
	}
	void Push(int i)
	{ // propagate lazy value
		Apply(i << 1, lazy[i]);
		Apply(i << 1 | 1, lazy[i]);
		lazy[i] = id;
	}
	void Pull(int i)
	{
		tree[i] = M(tree[i << 1], tree[i << 1 | 1]);
	}
};

using NodeType = std::pair<int, int>;
using LazyType = bool;

constexpr NodeType e = {0, 1};
constexpr LazyType id = false;

struct F_Merge
{
	NodeType operator()(const NodeType &p1, const NodeType &p2)
	{
		return {p1.first + p2.first, p1.second + p2.second};
	}
};

struct F_Update
{
	NodeType operator()(const LazyType doFlip, const NodeType &n)
	{
		if (doFlip)
			return {n.second - n.first, n.second};
		return n;
	}
};

struct F_Compose
{
	LazyType operator()(const LazyType l1, const LazyType l2)
	{
		return l1 ^ l2;
	}
};

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, M, q, l, r;
	std::cin >> N >> M;
	LazySegTree<NodeType, LazyType, F_Merge, F_Update, F_Compose> db(N, e, id);
	db.Init();
	while (M--)
	{
		std::cin >> q >> l >> r;
		if (q) // range query
		{
			std::cout << (db.Query(l, r)).first << '\n';
		}
		else // range update
		{
			db.Update(l, r, true);
		}
	}
}
