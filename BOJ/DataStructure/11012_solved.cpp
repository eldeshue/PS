/*
	BOJ 11012

	2D 맵 정보가 주어지고, 이 맵의 영역을 표현한 M개의 쿼리가 주어진다.
	각 쿼리가 표현하는 영역에 대해서, 해당 영역에 속하는 점의 개수의 총 합을 반환하기

	======================================================

	문제를 뒤집어서 각 집마다 몇 개의 퍼레이드 구역이 걸렸는지 counting한다.

	x기준 정렬 후 스위핑

	counting 세그먼트 트리로 덮여진 y 영역 정보를 저장

	퍼레이드 구간을 정의하는 사각형에 대하여,

	왼쪽 선을 만나면 +1 range update, 오른쪽 선을 만나면 -1 range update를 함.

	계란을 던지는 사람을 만나면 현재 range에 대해서 point query
	해당 좌표에 덮여진 영역의 갯수를 count, accumulate 한다.

	==================================================================

	lazy segtree로도 풀 수 있고, 또 persistent segment tree 풀이가 유명한 듯 싶은데,

	7626번에서 경험을 고려하면,
	counting segtree는 기본 segtree로도 range update는 할 수 있음

	이를 활용하면 그냥 풀 수 있을 듯 싶음.
*/
#include <iostream>
#include <vector>
#include <algorithm>

int constexpr log2(int n)
{
	int result = 0;
	while (n > (1 << result))
		result++;
	return result;
}

struct Event {
	int x;
	int y1, y2;
	int delta;	// 0 : point query

	// x좌표 기준으로 정렬
	bool operator<(const Event& other) const {
		if (x == other.x)
			return delta > other.delta;
		return x < other.x;
	}
};

std::vector<int> Y;
std::vector<int> segtree;

// custom segtree, range update cnt
void update(int node, int node_left, int node_right, int query_start, int query_end, int delta) {
	// base case, exit
	if (query_end < node_left || node_right < query_start) {
		return;
	}

	// full cover segment
	if (query_start <= node_left && node_right <= query_end) {
		segtree[node] += delta;
	}
	// partial cover segment
	else {
		int mid = (node_left + node_right) / 2;
		// left
		update(node * 2, node_left, mid, query_start, query_end, delta);
		// right
		update(node * 2 + 1, mid + 1, node_right, query_start, query_end, delta);
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int T, N, M;
	std::cin >> T;
	while (T--)
	{
		std::cin >> N >> M;	// egg, days
		std::vector<Event> events;
		int x, y;
		for (int i = 0; i < N; ++i)
		{
			std::cin >> x >> y;
			events.push_back({ x, y, y, 0 });
		}
		int l, r, b, t;
		for (int i = 0; i < M; ++i)
		{
			std::cin >> l >> r >> b >> t;
			events.push_back({ l, b, t, 1 });
			events.push_back({ r, b, t, -1 });
		}

		int constexpr MAX_CONTENTS = 100000;
		int constexpr depth = log2(MAX_CONTENTS);
		int constexpr size = 1 << depth;
		segtree.resize(size << 1, 0);
		auto point_sum_query = [&](int n) {
			n |= size;
			int result = 0;
			while (n > 0) {
				result += segtree[n];
				n >>= 1;
			}
			return result;
			};

		// sweeping
		std::sort(events.begin(), events.end());

		int result = 0;
		for (auto const& e : events)
		{
			if (e.delta)
			{
				// update query
				update(1, 0, size - 1, e.y1, e.y2, e.delta);
			}
			else
			{
				// point sum query
				result += point_sum_query(e.y1);
			}

		}

		std::cout << result << '\n';
	}
}
