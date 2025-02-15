/*
	BOJ 16357. Circuits

	lazy segment tree
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <unordered_map>

using pii = std::pair<int, int>;

template <typename NodeType,
		  typename LazyType,
		  typename F_Merge,
		  typename F_Update,
		  typename F_Composition>
struct LazySegTree
{ // 1-indexed
public:
	using A = NodeType;
	using B = LazyType;
	LazySegTree() : LazySegTree(0, A(), B()) {}
	explicit LazySegTree(int n, const A &e, const B &id)
		: n(n), e(e), id(id), lg(Log2(n)), sz(1 << lg), tree(sz << 1, e), lazy(sz, id) {}
	void Set(int i, const A &val) { tree[--i | sz] = val; }
	void Init()
	{
		for (int i = sz - 1; i; i--)
			Pull(i);
	}
	void Update(int i, const B &f)
	{
		--i |= sz;
		for (int j = lg; j; j--)
			Push(i >> j); // propagate prev lazy.
		Apply(i, f);
		for (int j = 1; j <= lg; j++)
			Pull(i >> j);
	}
	void Update(int l, int r, const B &f)
	{ /// range update
		--l |= sz, --r |= sz;
		// top to bottom, propagate previously setted lazy value
		for (int i = lg; i; i--)
		{
			if (l >> i << i != l)
				Push(l >> i);
			if (r + 1 >> i << i != r + 1)
				Push(r >> i);
		}
		// set new lazy value
		for (int L = l, R = r; L <= R; L >>= 1, R >>= 1)
		{
			if (L & 1)
				Apply(L++, f);
			if (~R & 1)
				Apply(R--, f);
		}
		// bottom to top, update parent
		for (int i = 1; i <= lg; i++)
		{
			if (l >> i << i != l)
				Pull(l >> i);
			if (r + 1 >> i << i != r + 1)
				Pull(r >> i);
		}
	}
	A Query(int i)
	{ // point query
		--i |= sz;
		for (int j = lg; j; j--)
			Push(i >> j); // propagate lazy
		return tree[i];
	}
	A Query(int l, int r)
	{ // range query
		A L = e, R = e;
		--l |= sz, --r |= sz;
		for (int i = lg; i; i--)
		{ // propagate lazy value
			if (l >> i << i != l)
				Push(l >> i); // to lazy propagate, get leaf of lazy tree
			if (r + 1 >> i << i != r + 1)
				Push(r >> i);
		}
		for (; l <= r; l >>= 1, r >>= 1)
		{ // query
			if (l & 1)
				L = M(L, tree[l++]);
			if (~r & 1)
				R = M(tree[r--], R);
		}
		return M(L, R);
	}

private:
	const int n, lg, sz;
	const A e;
	const B id;
	std::vector<A> tree;
	std::vector<B> lazy;
	F_Merge M;
	F_Update U;
	F_Composition C;
	static int Log2(int n)
	{
		int ret = 0;
		while (n > 1 << ret)
			ret++;
		return ret;
	}
	void Apply(int i, const B &f)
	{ // update and set lazy value
		tree[i] = U(f, tree[i]);
		if (i < sz)
			lazy[i] = C(f, lazy[i]);
	}
	void Push(int i)
	{ // propagate lazy value
		Apply(i << 1, lazy[i]);
		Apply(i << 1 | 1, lazy[i]);
		lazy[i] = id;
	}
	void Pull(int i)
	{
		tree[i] = M(tree[i << 1], tree[i << 1 | 1]);
	}
};

// merge seg-node
struct AddInt
{
	int operator()(const int n1, const int n2)
	{
		return n1 + n2;
	}
};

struct CompareSecondFirst // for pq, gireater than -> min heap
{
	bool operator()(const pii &r1, const pii &r2)
	{
		if (r1.second == r2.second)
			return r1.first > r2.first;
		return r1.second > r2.second;
	}
};

struct GetMaxInt
{
	int operator()(const int n1, const int n2)
	{
		return std::max(n1, n2);
	}
};

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	std::cin >> N;
	std::vector<pii> rectangles(N);
	std::vector<int> coordinates(2 * N);
	for (int i = 0; i < N; ++i) // get y coordinate, skip x, line is horizontal
	{
		int ux, uy, vx, vy;
		std::cin >> ux >> uy >> vx >> vy;

		rectangles[i].first = vy; // first < second
		rectangles[i].second = uy;

		// for coordinate compressioin
		coordinates[2 * i] = vy;
		coordinates[2 * i + 1] = uy;
	}
	// sort data for sweeping, first comes first
	std::sort(rectangles.begin(), rectangles.end());

	// coordinate compression
	// 좌표 압축을 통해서 세그트리에 집어넣을 수 있도록 전처리를 수행해야 함.
	// 겹침 관계를 유지하면서, 그 길이를 최소로 줄임. 즉 좌로 정렬.
	// first는 왼쪽, right는 오른쪽을 의미함.
	// sort coordinates for compression, closed range
	std::sort(coordinates.begin(), coordinates.end());
	coordinates.erase(std::unique(coordinates.begin(), coordinates.end()), coordinates.end()); // erase multiple items
	std::unordered_map<int, int> compressedCoordinates;
	for (int i = 0; i < coordinates.size(); ++i)
	{
		compressedCoordinates.insert(std::make_pair(coordinates[i], i + 1)); // seg tree 1-indexed
	}
	for (auto &range : rectangles) // convert range to compressed coordinate
	{
		range.first = compressedCoordinates[range.first];
		range.second = compressedCoordinates[range.second];
	}

	// lazy seg tree
	// 찔린 기판의 개수를 레이지 세그트리로 계산.
	// 전체 기판의 범위를 lazy seg tree에 세팅
	// 두 젓가락에 찔린 층의 개수에 중복을 제거하기 위해서
	// 왼쪽 젓가락에 찔린 기판들을 range update로 제외해줌(개수는 세어둬야 함)
	// 왼쪽 젓가락에 의해서 제외된 기판들은 왼쪽 젓가락의 이동에 따라서 복원이 필요함
	// 따라서 이 제외/복원을 우선순위 큐로 수행해줄것
	// 오른쪽 젓가락은 대충 point query를 사용하면 됨.
	const int maxRange = coordinates.size();
	LazySegTree<int, int, GetMaxInt, AddInt, AddInt> overlappedCounter(maxRange, 0, 0);
	for (const auto [l, r] : rectangles)
	{
		overlappedCounter.Update(l, r, 1);
	}

	// sweeping
	// 두 젓가락을 움직이면서 최댓값을 찾음.
	// 두 젓가락에 동시에 찔려도 하나로 계산해야 함.
	// 우선순위 큐 두 개를 써서 복원될 사각형과 제외될 사각형을 운영해줘야 한다.
	// toBeRecovered.
	// toBeRecovered는 second를 기준으로 하는 min heap
	// 제외 자체는 정렬된 배열을 보고 수행함.
	std::priority_queue<pii, std::vector<pii>, CompareSecondFirst> currentLeftRange;
	int eraseCursor = 0;
	int result = 0;
	for (int left = 1; left < maxRange; ++left)
	{
		// restore
		while (!currentLeftRange.empty() && currentLeftRange.top().second < left) // closed range,
		{
			const auto [rLeft, rRight] = currentLeftRange.top();
			currentLeftRange.pop();
			overlappedCounter.Update(rLeft, rRight, 1); // recover range
		}
		// erase and push priority queue
		while (eraseCursor < rectangles.size() && rectangles[eraseCursor].first <= left)
		{
			const auto &[eLeft, eRight] = rectangles[eraseCursor];
			overlappedCounter.Update(eLeft, eRight, -1);	// erase range
			currentLeftRange.push(rectangles[eraseCursor]); // to recover range, save
			eraseCursor++;
		}
		// update result, max
		// left count : number of range in the pq
		// right count : maximum value of right which is after left
		result = std::max(result, static_cast<int>(currentLeftRange.size()) + overlappedCounter.Query(left + 1, maxRange));
	}
	std::cout << result;
}
