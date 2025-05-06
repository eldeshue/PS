
#include <iostream>
#include <tuple>

#include <vector>
#include <algorithm>
#include <functional>

/*
	Merge Sort tree

	E_Type has to be comparable(or implement comparator)
	R_Type has to be addable, overload operator+
*/
template<typename E_Type, typename R_Type>
class MergeSortTree { // 1-indexed
private:
	MergeSortTree() = delete;
	MergeSortTree(MergeSortTree const&) = delete;
	MergeSortTree& operator=(MergeSortTree const&) = delete;

	using ElemType = E_Type;
	using A = std::vector<ElemType>;
	using Comp = std::function<bool(ElemType const&, ElemType const&)>;

	const int n, lg, sz;
	std::vector<A> tree;
	const R_Type e;

	static int Log2(int n) { int ret = 0; while (n > 1 << ret) ret++; return ret; } // up scale
public:
	explicit MergeSortTree(int n, R_Type e) : n(n), lg(Log2(n)), sz(1 << lg), tree(sz << 1, A()), e(e) {}
	void Set(int i, const ElemType& val) { tree[--i | sz].push_back(val); }	// fill leaf node, 1 indexed
	void Init()	// comparable Element type
	{
		for (int i = sz - 1; i; i--)
		{
			auto const& left_segment = tree[i << 1];
			auto const& right_segment = tree[i << 1 | 1];

			// merge left and right, sorted, O(N)
			std::merge(
				left_segment.begin(), left_segment.end(),
				right_segment.begin(), right_segment.end(),
				std::back_inserter(tree[i])
			);
		}
	}
	void Init(Comp cmp)	// explicit comparator needed
	{
		for (int i = sz - 1; i; i--)
		{
			auto const& left_segment = tree[i << 1];
			auto const& right_segment = tree[i << 1 | 1];

			// merge left and right, sorted, O(N)
			std::merge(
				left_segment.begin(), left_segment.end(),
				right_segment.begin(), right_segment.end(),
				std::back_inserter(tree[i]), cmp
			);
		}
	}
	R_Type Query(int l, int r, std::function<R_Type(A const& seg)> f) const {
		R_Type L = e, R = e;
		for (--l |= sz, --r |= sz; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) L += f(tree[l++]);
			if (~r & 1) R += f(tree[r--]);
		}
		return L + R;
	}
};

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	using Q = std::tuple<int, int, int>;

	// input
	int N, M;
	std::cin >> N;
	std::vector<int> nums(N, 0);
	for (auto& n : nums) std::cin >> n;
	std::cin >> M;
	std::vector<Q> queries(M);
	for (auto& [l, r, k] : queries) std::cin >> l >> r >> k;

	// init merge-sort tree
	MergeSortTree<int, int> st(N, 0);
	for (int i = 0; i < N; ++i) st.Set(i + 1, nums[i]);
	st.Init(std::less<int>());

	// handling query
	for (auto& [l, r, k] : queries) std::cout << st.Query(l, r, [k](std::vector<int> const& seg) -> int {
		return std::distance(std::upper_bound(seg.begin(), seg.end(), k), seg.end());
		}) << '\n';
}

