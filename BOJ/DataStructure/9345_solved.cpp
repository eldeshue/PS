/*
	BOJ 9345

	N개의 원소가 각각 제자리에 위치한 상태로 시작.
	다음의 쿼리를 처리한다.

	1. 임의의 두 원소의 자리를 바꾼다
	2. 주어진 범위 내의 원소가 모두 존재하는지 확인

	=====================================
	<원본 위치에서 이동한 거리를 추적하는 segtree>
	최초에는 모두가 자기 위치에 있으므로 세그먼트 트리 전체를 0으로 시작,
	1번 switch query는 왼쪽으로 이동한 원소는 이동한 거리만큼 -, 반대는 +
	2번 range쿼리를 날렸을 때, range의 합이 0이면 true, 0이 아니면 false

	-> failed, 반례
	1
	5 3
	0 0 3
	0 1 4
	1 1 3

	NO

	거리만 추적해서는 잘못된 구간을 잡아도 우연히 구간 합이 상쇄될 수 있음.
	=====================================
	<구간 최대 및 최소를 유지하는 segtree>
	swap이 발생해도, yes를 받는 구간은 swap의 결과가 해당 구간 내에서 이루어짐을 의미.

	따라서, 구간의 원소에 대해서 질문을 받을 때, 구간을 벗어난 원소가 있는지 확인
	-> 답.
*/
#include <iostream>
#include <vector>

template<typename NodeType1, typename F_Merge>
struct SegTree { // 1-indexed
public:
	using A = NodeType1;
	SegTree() : SegTree(0, A()) {}
	explicit SegTree(int n, const A& e) : n(n), lg(Log2(n)), sz(1 << lg), e(e), tree(sz << 1, e) {}
	void Set(int i, const A& val) { tree[--i | sz] = val; }
	void Init() { for (int i = sz - 1; i; i--) tree[i] = M(tree[i << 1], tree[i << 1 | 1]); }
	void Update(int i, const A& val) {
		tree[--i |= sz] = val;  // leaf
		while (i >>= 1) tree[i] = M(tree[i << 1], tree[i << 1 | 1]);    // merge, climb up
	}
	A Query(int i) const { return tree[--i | sz]; }
	A Query(int l, int r) const {
		A L = e, R = e;
		for (--l |= sz, --r |= sz; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) L = M(L, tree[l++]);     // if l is odd
			if (~r & 1) R = M(tree[r--], R);    // if r is even
		}
		return M(L, R);
	}
private:
	const int n, lg, sz; const A e; std::vector<A> tree; F_Merge M;
	static int Log2(int n) { int ret = 0; while (n > 1 << ret) ret++; return ret; } // up scale
};

using NodeType = std::pair<int, int>;

struct RangeMerge
{
	NodeType operator()(NodeType const& i1, NodeType const& i2) const
	{
		return NodeType(std::min(i1.first, i2.first), std::max(i1.second, i2.second));
	}
};

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int T;
	std::cin >> T;
	while (T--)
	{
		int N, K;
		std::cin >> N >> K;
		SegTree<NodeType, RangeMerge> range_tree(N, { 2e9, -2e9 });
		for (int i = 1; i <= N; ++i)
			range_tree.Set(i, { i, i });
		range_tree.Init();
		while (K--)
		{
			int Q, A, B;
			std::cin >> Q >> A >> B;
			++A, ++B;
			if (Q)
			{
				// range query
				auto const [l, r] = range_tree.Query(A, B);
				//				std::cout << "debug : " << l << ' ' << r << '\n';
				if (A == l && B == r)
					std::cout << "YES\n";
				else
					std::cout << "NO\n";
			}
			else
			{
				// switch query
				// range update
				auto pA = range_tree.Query(A);
				auto pB = range_tree.Query(B);
				range_tree.Update(A, pB);
				range_tree.Update(B, pA);
			}
		}
	}
}

