
#include <iostream>
#include <vector>
/*
 * From : BOJ blog, https://www.acmicpc.net/blog/view/117#comment-714 
 * Author : jinhan814
 * Date : 2022-04-16
 * Description : Non-recursive implementation of Segment Tree
 */

template<typename NodeType, typename F_Merge>
struct SegTree { // 1-indexed
public:
    using A = NodeType;
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

typedef int NodeType;
constexpr NodeType e1 = 2147483647;
constexpr NodeType e2 = 0;

struct F_Merge_Min {
    NodeType operator() (const NodeType& a, const NodeType& b) const {
        return std::min(a, b);
    }
};

struct F_Merge_Max {
    NodeType operator() (const NodeType& a, const NodeType& b) const {
        return std::max(a, b);
    }
};

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

    int N, M;
    std::cin >> N >> M;
    SegTree<NodeType, F_Merge_Min> minSegTree(N, e1);
    SegTree<NodeType, F_Merge_Max> maxSegTree(N, e2);
    for (int i = 1; i <= N; ++i)
    {
        int input;
        std::cin >> input;
        minSegTree.Set(i, input);
        maxSegTree.Set(i, input);
    }
    minSegTree.Init();
    maxSegTree.Init();
    for (int i = 0; i < M; ++i)
    {
        int l, r;
        std::cin >> l >> r;
        std::cout << minSegTree.Query(l, r) << ' ' << maxSegTree.Query(l, r) << '\n';
    }
}
