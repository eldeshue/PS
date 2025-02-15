
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
        tree[--i |= sz] += val;  // leaf
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

typedef long long NodeType;
constexpr NodeType e = 0;

struct F_Merge {
    NodeType operator() (const NodeType& a, const NodeType& b) const
    {
        return a + b;
    }
};

/*
    use segtree to count elements

    세그먼트 트리를 숫자를 카운팅하는 방법으로 사용함.
    누적합 세그먼트 트리에 인덱스를 카운팅하려는 원소로 삼으면
    레인지 쿼리를 통해서 지금까지 원소 중 몇 개가 어느 범위에 있는지 알 수 있다.

    문제에서 요구하는 바는 현재 원소 왼쪽에 있는 원소 중, 자신보다 큰 원소의 개수를 모두 더하는 것.
    따라서, 왼쪽부터 순서대로 세그먼트 트리에 넣으면서, 해당 원소보다 큰 원소의 수를 query로 찾는다.

    단, 해당 풀이가 통하려면, 원소의 범위가 한정되어 있어야 한다.
    상 하한이 정해져야만, 세그먼트 트리를 만들 수 있기 때문이다.
*/

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

    NodeType N, cnt = 0;
    std::cin >> N;
    SegTree<NodeType, F_Merge> st(N, e);
    for (int i = 0; i < N; ++i)
    {
        int num;
        std::cin >> num;
        cnt += st.Query(num, N);
        st.Update(num, 1);
    }
    std::cout << cnt;
}