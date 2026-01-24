/*
	BOJ 1017

	합이 소수를 이루는 파티션에 대한 이분 매칭

	---

	기본적으로 조합 최적화 문제
	모든 수를 다 짝지었다(쌍을 이룬다)? -> 매칭, 이분 그래프

	에라토스테네스의 채를 사용해서 합이 소수를 이루는 경우에 edge를 추가한 이분 그래프

	이후 첫 노드와 쌍을 이루는 노드를 하나 잡아서 고정하고,
	이 두 노드가 존재하지 않는 그래프에 대해 이분 매칭을 수행,
	N-1개의 매칭이 존재하는지 여부를 확인

	---

	N이 최대 50인데, 이분 그래프로 만들면 N이 100임.

	hopcroft-karp가 N^2.5이므로, 하나의 쌍을 고정하므로, N * N^2.5 => N^3.5임.

	100^3.5 = 10^7 가능!
*/
#include <vector>

class Sieve {
private:
	Sieve() = delete;
	Sieve(Sieve const&) = delete;
	Sieve& operator=(Sieve const&) = delete;

	std::vector<bool> prime;

	inline void sparse_init(
		size_t start,
		size_t stride,
		bool val) {
		for (size_t i = start; i < prime.size(); i += stride) {
			prime[i] = val;
		}
	}

public:
	// Sieve of Erastosthenes with Wheeling 
	explicit Sieve(size_t N) : prime(N + 1, false) {
		if (N < 2) return;
		if (N >= 2) prime[2] = true;
		if (N >= 3) prime[3] = true;
		if (N < 5) return;

		// 5이하의 두 소수 2,3 check
		prime[2] = prime[3] = true;

		// 5이상의 모든 소수는 6K +- 1의 형태를 가짐.
		// 이들에 대해서만 sieve를 수행
		sparse_init(5, 6, true);
		sparse_init(7, 6, true);
		for (size_t p = 5, p_sq = 25; p_sq <= N;) {
			// 6k +- 1의 꼴을 갖는, 다음 소수 후보를 구하는 gap
			size_t gap = (p + 3) % 6; // 6k - 1이면 +2, 6k + 1이면 +4 해줘야 함

			// if p is prime, erase mult of p
			if (prime[p] == true) {
				// 6k +- 1인 값들만 지워야 함
				// 6의 배수가 아닌 p의 배수는 이미 지워짐
				// 따라서 stride에 6을 곱해서 6배 빠르게 계산하기
				size_t stride = p * 6;
				sparse_init(p_sq, stride, false);

				// 만약 p가 6k + 1의 꼴이었다면 위에서는 6k+1만 지웠음
				// p의 배수 중에서 6k - 1의 꼴도 지워줘야 함
				// stride를 6배 크게 잡았기 때문
				// p * (p + gap) = p^2 + p * gap
				if (p_sq + gap * p <= N)
					sparse_init(p_sq + gap * p, stride, false);
			}
			p += gap;
			p_sq = p * p;	// p squared
		}
	}
	Sieve(Sieve&& other) noexcept : prime(std::move(other.prime)) {}
	Sieve& operator=(Sieve&& other) noexcept {
		if (this != &other) {
			prime = std::move(other.prime);
		}
		return *this;
	}

	bool is_prime(uint32_t n) const {
		return n < prime.size() && prime[n];
	}

	std::vector<bool> const& data() const { return prime; }
};

#include <queue>
#include <tuple>

class HopcroftKarpSolver
{
private:
	// less than offset is left, from 0 to offset - 1
	// else right
	using pii = std::pair<int, int>;
	int offset;
	const std::vector<std::vector<int>>& graph;
	std::vector<int> matchedNodes;
	std::vector<int> distLayer;

	bool isLeft(const int nodeId) const { return (nodeId < offset); }
	bool isFreeNode(const int nodeId) { return (matchedNodes[nodeId] == -1); };
	bool isMatchedEdge(const int lNode, const int rNode) { return (matchedNodes[lNode] == rNode); };
	// find minimum distance of aug path
	int bfs()
	{
		std::queue<pii> q;
		bool augFlag = false;
		int minAugDist = 0;

		fill(distLayer.begin(), distLayer.end(), -1);
		for (int lNode = 0; lNode < offset; ++lNode)
		{
			// all left and unmatched nodes
			if (isFreeNode(lNode))
			{
				distLayer[lNode] = 0;
				q.push(std::make_pair(lNode, 0));
			}
		}
		while (!q.empty())
		{
			int curNode, curDist;
			std::tie(curNode, curDist) = q.front();
			q.pop();
			if (augFlag == true && curDist > minAugDist)
			{
				// no more aug path
				break;
			}
			else if (!isLeft(curNode) && !isFreeNode(curNode)) // current node is right, use matched edge
			{
				const int& nextNode = matchedNodes[curNode];
				distLayer[nextNode] = curDist + 1;
				q.push(std::make_pair(nextNode, curDist + 1));
			}
			else // current node is left
			{
				for (const int& nextNode : graph[curNode])
				{
					// finding unmatched edge
					if (distLayer[nextNode] == -1 && !isMatchedEdge(curNode, nextNode))
					{
						distLayer[nextNode] = curDist + 1;
						q.push(std::make_pair(nextNode, curDist + 1));
						if (!augFlag && !isLeft(nextNode) && isFreeNode(nextNode))
						{
							augFlag = true;
							minAugDist = curDist + 1;
						}
					}
				}
			}
		}
		return minAugDist;
	}
	bool dfs(const int curNode, const int curDist)
	{
		// base case
		if (curDist == 0 && isLeft(curNode) && isFreeNode(curNode))
		{
			return true;
		}
		else if (isLeft(curNode)) // follow matched edge
		{
			return dfs(matchedNodes[curNode], curDist - 1);
		}
		else // follow unmatched edge
		{
			for (const int& nextNode : graph[curNode])
			{
				// follow alternate path depend on distLayer
				if (distLayer[nextNode] == curDist - 1)
				{
					distLayer[nextNode] = -1;
					if (dfs(nextNode, curDist - 1))
					{
						matchedNodes[curNode] = nextNode;
						matchedNodes[nextNode] = curNode;
						return true;
					}
				}
			}
		}
		return false;
	}

public:
	HopcroftKarpSolver(int offset, const std::vector<std::vector<int>>& g)
		: offset(offset), graph(g), matchedNodes(g.size(), -1), distLayer(g.size(), false) {
	};

	// O(n ^ 2.5) !!!
	int maxMatch()
	{
		int targetDist = 0, maxMatchCnt = 0;
		while (true)
		{
			// find augment path using bfs
			targetDist = bfs();

			if (targetDist == 0)
			{
				break; // no augment path, maximum matching
			}
			// update augment path using dfs
			for (int node = 0; node < distLayer.size(); ++node)
			{
				// dfs, if dfs == true -> result++
				if (matchedNodes[node] == -1 && distLayer[node] == targetDist)
				{
					distLayer[node] = -1;
					if (dfs(node, targetDist))
						maxMatchCnt++;
				}
			}
		}
		return maxMatchCnt;
	}
};

#include <iostream>
#include <algorithm>

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	int N;
	std::cin >> N;
	std::vector<int> nums(N);
	for (auto& n : nums)
		std::cin >> n;

	// sieve of eratosthenes, reuse
	// max of each value is 1000
	// so, max of sum is 2000
	Sieve s(2000);

	// build bipartite graph
	// offset is N
	// do not link with self
	std::vector<std::vector<int>> graph(2 * N);
	for (int l = 0; l < N; ++l) {
		for (int r = 0; r < N; ++r) {
			if (l != r && s.is_prime(nums[l] + nums[r])) {
				// sum is prime, add edge
				graph[l].push_back(N + r);
				graph[N + r].push_back(l);
			}
		}
	}

	// move first node to the back
	for (auto& adj_list : graph) {
		// find link with first node
		auto itr = std::find(adj_list.begin(), adj_list.end(), 0);

		if (itr != adj_list.end()) {
			std::swap(*itr, adj_list.back());
		}
	}

	// solve, O(N^3.5)
	std::vector<std::vector<int>> erased_graph(2 * N);
	std::vector<int> result;
	for (int i = 0; i < graph[0].size(); ++i) {
		// get target node
		int const target_node = graph[0][i];

		// remake graph, without target node and first node
		// those matching is occupied
		for (auto& vec : erased_graph) {
			vec.clear();
		}
		for (int i = 1; i < graph.size(); ++i) { // first node is occupied
			if (i == target_node) continue;

			for (auto const node : graph[i]) {
				if (node != 0 && node != target_node)
					erased_graph[i].push_back(node);
			}
		}

		// bipartite matching, with solver
		// O(N^2.5)
		HopcroftKarpSolver hks(N, erased_graph);
		int match_cnt = hks.maxMatch();

		// update result
		if (match_cnt == N - 1) {
			result.push_back(nums[target_node - N]);
		}
	}

	// print
	if (result.empty()) {
		std::cout << -1;
	}
	else {
		// ascending order
		std::sort(result.begin(), result.end());
		for (auto const r : result) {
			std::cout << r << ' ';
		}
	}
}
