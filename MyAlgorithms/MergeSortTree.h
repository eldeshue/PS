
#ifndef MERGE_SORT_TREE_H
#define MERGE_SORT_TREE_H

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
	void Init()	// comparable Element type, need to be sorted before init
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
	void Init(Comp cmp)	// explicit comparator needed, need to be sorted before init
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

#endif
