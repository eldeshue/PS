/*
 * From : BOJ blog, https://www.acmicpc.net/blog/view/117#comment-714 
 * Author : jinhan814
 * Date : 2022-04-16
 * Description : Non-recursive implementation of Segment Tree
 */

#include <iostream>
#include <vector>

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

class NodeType
{
public:
    int idx;
    int val;
    NodeType(int idx, int val) : idx(idx), val(val) {};
};

const NodeType e(2147483647, 2147483647);

struct F_Merge {
    NodeType operator() (const NodeType& a, const NodeType& b) const {
        if (b.val >= a.val)
            return a;
        else
            return b;
    }
};

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

    int size, num_query;
    std::cin >> size;
    SegTree<NodeType, F_Merge> ST(size, e);
    for (int i = 1; i <= size; ++i)
    {
        int val;
        std::cin >> val;
        ST.Set(i, NodeType(i, val));
    }
    ST.Init();
    std::cin >> num_query;
    for (int i = 0; i < num_query; ++i)
    {
        int query_type;
        std::cin >> query_type;
        if (query_type == 1)
        {
            int i, v;
            std::cin >> i >> v;
            ST.Update(i, NodeType(i,v));
        }
        else if (query_type == 2)
        {
            int i, j;
            std::cin >> i >> j;
            std::cout << ST.Query(i, j).idx << '\n';
        }
    }
}