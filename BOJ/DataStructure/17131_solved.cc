/*
	BOJ 17131

	점들을 정렬하여 sweeping
	5419번이 특정 방향으로 꺾이는 선을 이루는 쌍을 구하는 문제였다면,
	이 문제는 한 발 더 나아가 브이자를 이루는 세 점을 구하는 문제임.

	sweeping을 두 번 수행하면 될 일
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <deque>
#include <numeric>

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
	const int n, lg, sz; const A e; std::vector<A> tree; F_Merge M;
	static int Log2(int n) { int ret = 0; while (n > 1 << ret) ret++; return ret; } // up scale
};

constexpr int DIV = 1000000007;

struct Add {
	int operator()(int const n1, int const n2) const {
		return (n1 + n2) % DIV;
	}
};

using tiii = std::tuple<int, int, int>;

void compress_y_coordinate(std::vector<tiii>& coordinates) {
	std::map<int, int> map;

	for (auto const& [x, y, cnt] : coordinates) {
		map.insert({ y, 0 });
	}

	int compressed = 1;
	for (auto& [origin, mapped] : map) {
		mapped = compressed++;
	}

	// mapping
	for (auto& [x, y, cnt] : coordinates) {
		y = map[y];
	}
}


int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int  N;
	std::cin >> N;
	std::vector<tiii> points(N);
	for (auto& [x, y, cnt] : points) {
		std::cin >> x >> y;
		cnt = 1;
	}

	// 좌표 압축, 0~N
	// segment tree에 y좌표를 집어넣으려면 y좌표값을 압축해줘야 함.
	compress_y_coordinate(points);

	SegTree<ll, Add> ys(N, 0LL);

	using pii = std::pair<int, int>;
	std::deque<tiii> update_queue;

	// first sweeping
	// sort
	std::sort(points.begin(), points.end(),
		[](auto const& p1, auto const& p2) {
			auto const& [x1, y1, c1] = p1;
			auto const& [x2, y2, c2] = p2;
			if (x1 == x2) {
				return y1 > y2;	// y는 내림차순
			}
			return x1 < x2; // x는 오름차순
		});
	for (auto& [x, y, cnt] : points) {
		// update
		if (!update_queue.empty() && std::get<0>(update_queue.back()) < x) {
			while (!update_queue.empty()) {
				// update seg tree
				auto const [px, py, pc] = update_queue.front();
				update_queue.pop_front();

				ys.Update(py, (ys.Query(py) + pc) % DIV);
			}
		}


		// 
		int temp = 0;
		if (y < N)
			temp = ys.Query(y + 1, N);

		// query
		update_queue.push_back({ x, y, cnt });

		// update sum
		cnt = temp;
	}

	// second sweeping
	std::fill(ys.tree.begin(), ys.tree.end(), 0);
	update_queue.clear();

	std::sort(points.begin(), points.end());
	for (auto& [x, y, cnt] : points) {
		// update
		if (!update_queue.empty() && std::get<0>(update_queue.back()) < x) {
			while (!update_queue.empty()) {
				// update seg tree
				auto const [px, py, pc] = update_queue.front();
				update_queue.pop_front();

				ys.Update(py, (ys.Query(py) + pc) % DIV);
			}
		}

		// 
		int temp = 0;
		if (y > 1)
			temp = ys.Query(1, y - 1);

		// query
		update_queue.push_back({ x, y, cnt });

		// update sum
		cnt = temp;
	}

	std::cout << std::accumulate(points.begin(), points.end(), 0,
		[](int const acc, auto const& p) {
			return (acc + std::get<2>(p)) % DIV;
		});
}
