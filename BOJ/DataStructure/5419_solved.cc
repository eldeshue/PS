/*
	BOJ 5419

	https://www.acmicpc.net/problem/5419

	점들을 정렬하여 sweeping

	공간에서 데이터 처리하는 흔한 테크닉
	이전 N모회사의 문제, 평면에서 가장 가까운 두 점 찾기에서 봤던 sweeping 테크닉임.
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using ll = long long;

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

struct Add {
	int operator()(int const n1, int const n2) const {
		return n1 + n2;
	}
};

using pii = std::pair<int, int>;

void compress_y_coordinate(std::vector<pii>& coordinates) {
	std::map<int, int> map;

	for (auto const& [x, y] : coordinates) {
		map.insert({ y, 0 });
	}

	int compressed = 1;
	for (auto& [origin, mapped] : map) {
		mapped = compressed++;
	}

	// mapping
	for (auto& [x, y] : coordinates) {
		y = map[y];
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int  T, N;
	std::cin >> T;
	while (T--) {
		std::cin >> N;
		std::vector<pii> points(N);
		for (auto& [x, y] : points)
			std::cin >> x >> y;

		// sort
		std::sort(points.begin(), points.end(),
			[](auto const& p1, auto const& p2) {
				if (p1.first == p2.first) {
					return p1.second > p2.second;	// y는 내림차순
				}
				return p1.first < p2.first; // x는 오름차순
			});

		// 좌표 압축, 0~N
		// segment tree에 y좌표를 집어넣으려면 y좌표값을 압축해줘야 함.
		compress_y_coordinate(points);

		// sweep
		// seg tree 도입하여 원소 개수 count
		SegTree<ll, Add> ys(N, 0LL);
		ys.Init();
		ll result = 0LL;
		for (auto const& [x, y] : points) {
			result += ys.Query(y, N);	// range query, num of elem eq or above y
			ys.Update(y, ys.Query(y) + 1);	// increase 1
		}
		std::cout << result << '\n';
	}
}
