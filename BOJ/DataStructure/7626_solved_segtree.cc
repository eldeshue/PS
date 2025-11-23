/*
	BOJ 7626

	https://www.acmicpc.net/problem/7626

	사각형을 분해해서 양 끝에 존재하는 y축에 평행한 두 선을 정렬, 이벤트로 삼는다.
	왼쪽 선을 만나면 그 선이 점유한 범위를 증가시키고,
	오른 쪽 선을 만나면 점유한 범위를 감소시킨다.

	여기서 각 선을 만날 때 마다, 이전 선과 떨어진 거리 만큼을 현재 전체 점유
	(즉, cnt가 1 이상인 범위)에 곱해서 총 점유 범위를 계산한다.
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

struct UpdateEvent {
	int x;
	int y1, y2;
	int delta;

	// x좌표 기준으로 정렬
	bool operator<(const UpdateEvent& other) const {
		return x < other.x;
	}
};

struct Node {
	int cnt;        // 이 구간을 덮는 사각형의 개수
	long long len;  // 이 구간에서 덮인(cnt > 0) '물리적' y길이의 합
	Node() : cnt(0), len(0) {}
};

std::vector<int> Y;
std::vector<Node> segtree;

// custom segtree, range update cnt
void update(int node, int node_left, int node_right, int query_start, int query_end, int delta) {
	// base case, exit
	if (query_end < node_left || node_right < query_start) {
		return;
	}

	// full cover segment
	if (query_start <= node_left && node_right <= query_end) {
		segtree[node].cnt += delta;
	}
	// partial cover segment
	else {
		int mid = (node_left + node_right) / 2;
		// left
		update(node * 2, node_left, mid, query_start, query_end, delta);
		// right
		update(node * 2 + 1, mid + 1, node_right, query_start, query_end, delta);
	}

	// update length
	// 현재 노드의 cnt > 0 이면, 자식 노드의 len과 관계없이
	// 이 노드 전체가 덮인 것입니다.
	if (segtree[node].cnt > 0) {
		// 물리적 길이: Y[node_right + 1] - Y[node_left]
		// Y배열은 m개의 좌표, 트리의 리프는 m-1개의 구간을 관리함
		segtree[node].len = Y[node_right + 1] - Y[node_left];
	}

	// merge
	// 현재 노드의 cnt == 0 이면, 이 노드를 통째로 덮는 사각형은 없습니다.
	else {
		// 리프 노드가 아니라면 (자식이 있다면)
		if (node_left != node_right) {
			segtree[node].len = segtree[node << 1].len + segtree[(node << 1) | 1].len;
		}
		// 리프 노드인데 cnt == 0 이면
		else {
			segtree[node].len = 0;
		}
	}
}


int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	std::cin >> N;

	std::vector<UpdateEvent> events;
	std::set<int> y_coords_map; // 중복 제거 및 좌표 압축

	for (int i = 0; i < N; ++i) {
		int x1, y1, x2, y2;
		std::cin >> x1 >> x2 >> y1 >> y2;

		events.push_back({ x1, y1, y2, 1 });  // start rectangle
		events.push_back({ x2, y1, y2, -1 }); // end rectangle

		y_coords_map.insert(y1);
		y_coords_map.insert(y2);
	}

	Y.reserve(y_coords_map.size());
	for (auto const& y : y_coords_map) {
		Y.push_back(y);
	}

	int m_intervals = Y.size() - 1;
	segtree.resize(4 * m_intervals);

	sort(events.begin(), events.end());

	// sweeping
	long long total_area = 0;
	for (int i = 0; i < events.size(); ++i) {
		if (i > 0) {
			long long dx = events[i].x - events[i - 1].x;
			long long covered_y_length = segtree[1].len; // get total, at root
			total_area += dx * covered_y_length;
		}

		// get range
		int y1_idx = lower_bound(Y.begin(), Y.end(), events[i].y1) - Y.begin();
		int y2_idx = lower_bound(Y.begin(), Y.end(), events[i].y2) - Y.begin();

		// update seg tree
		update(1, 0, m_intervals - 1, y1_idx, y2_idx - 1, events[i].delta);
	}

	std::cout << total_area << "\n";
}
