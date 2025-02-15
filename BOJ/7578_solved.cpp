
/*
#include <iostream>
#include <unordered_map>
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

struct ADDINT
{
    long long operator()(const long long n1, const long long n2) const
    {
        return n1 + n2;
    }
};

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    // input
    long long N;
    std::cin >> N;
    std::vector<long long> A(N), B(N);
    for (long long i = 0; i < N; ++i)
        std::cin >> A[i];
    for (long long i = 0; i < N; ++i)
        std::cin >> B[i];

    // coordinate compression
    std::unordered_map<long long, long long> transformTable;
    for (long long i = 0; i < N; ++i)
        transformTable.insert(std::make_pair(B[i], i + 1));
    for (long long i = 0; i < N; ++i)
        A[i] = transformTable[A[i]];

    // segtree
    // no setting, no initializing
    SegTree<long long, ADDINT> sortedLeftArr(N + 1, 0);
    long long swapCnt = 0;
    for (const long long n : A)
    {
        // use query
        swapCnt += sortedLeftArr.Query(n + 1, N + 1);
        // update query, increase 1
        sortedLeftArr.Update(n, sortedLeftArr.Query(n) + 1);
    }
    std::cout << swapCnt;
}
*/