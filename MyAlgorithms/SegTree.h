/*
 * From : BOJ blog, https://www.acmicpc.net/blog/view/117#comment-714 
 * Author : jinhan814
 * Date : 2022-04-16
 * Description : Non-recursive implementation of Segment Tree
 */
#ifndef SEGMENT_TREE
#define SEGMENT_TREE

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

#endif

// example
/*
struct NodeType {};
constexpr NodeType e;

typedef long long NodeType;
constexpr NodeType e = 0;

struct F_Merge {
    NodeType operator() (const NodeType& a, const NodeType& b) const {
    }
};
*/
//

/*
 * tree[ --i | sz ] : sz는 n보다 큰, 2의 거듭 제곱 수 중 가장 작은 것. 
 * 즉 sz는 leaf의 최대 개수를 뜻함(비어있는 leaf도 있음)
 * sz 와 |연산으로 더해서 leaf의 위치 특정.

*/