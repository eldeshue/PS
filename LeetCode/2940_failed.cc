
/*
	정수 배열이 주어짐

	어떤 포인터는 배열 위를 가리키고, 이 포인터는 배열 위를 이동함.
	포인터는 항상 오른 쪽으로 이동하고, 현재 위치보다 큰 값을 향해서 이동함.

	쿼리로 두 포인터의 시작 위치가 주어지고, 이 두 포인터가 이동할 때, 처음으로 겹치는 위치를 구함.

	배열의 크기(N) <= 5 * 10 ^ 4
	쿼리의 개수(M) <= 5 * 10 ^ 4

	naive하게 처리하면 M * N임. 하지만 TLE일 것이 명약광화 함.
	배열에 대한 전처리(N 혹은 N log N)를 수행한 후, 쿼리당 logN의 비용으로 처리해야 함.

	==================================================

	한 번 겹쳐지기 시작하면 그 이후는 동일함. 즉 정렬된 상태라는 뜻
	따라서, 이진 탐색을 사용할 수 있음. 다만, 이 경우는 메모리가 N^2이 될 것.

	그래프로 만들면 메모리도 N인데, 공통 조상 찾기를 해야 함.

	==================================================

	1. 쿼리와 셋업을 한 번에 수행하기

	쿼리를 모조리 정렬하여 주어진 배열을 순회하면서 쿼리를 처리하는 것
	쿼리를 다시 원본 방향으로 정렬하여 문제를 해결하기 혹은 원본 위치에 저장하기


*/
#include <iostream>
#include <vector>

using namespace std;

#pragma GCC optimize("03")
#pragma GCC target("avx")
#pragma GCC target("-fsplit-loops")
#include <algorithm>
#include <map>
#include <queue>
#include <tuple>

template <typename NodeType, typename F_Merge>
struct SegTree
{ // 1-indexed
public:
	using A = NodeType;
	SegTree() : SegTree(0, A()) {}
	explicit SegTree(int n, const A &e) : n(n), lg(Log2(n)), sz(1 << lg), e(e), tree(sz << 1, e) {}
	void Set(int i, const A &val) { tree[--i | sz] = val; }
	void Init()
	{
		for (int i = sz - 1; i; i--)
			tree[i] = M(tree[i << 1], tree[i << 1 | 1]);
	}
	void Update(int i, const A &val)
	{
		tree[--i |= sz] = val; // leaf
		while (i >>= 1)
			tree[i] = M(tree[i << 1], tree[i << 1 | 1]); // merge, climb up
	}
	A Query(int i) const { return tree[--i | sz]; }
	A Query(int l, int r) const
	{
		A L = e, R = e;
		for (--l |= sz, --r |= sz; l <= r; l >>= 1, r >>= 1)
		{
			if (l & 1)
				L = M(L, tree[l++]); // if l is odd
			if (~r & 1)
				R = M(tree[r--], R); // if r is even
		}
		return M(L, R);
	}

private:
	const int n, lg, sz;
	const A e;
	std::vector<A> tree;
	F_Merge M;
	static int Log2(int n)
	{
		int ret = 0;
		while (n > 1 << ret)
			ret++;
		return ret;
	} // up scale
};

struct MININT
{
	int operator()(const int n1, const int n2) const
	{
		return min(n1, n2);
	}
};

class Solution
{
private:
public:
	// solution method
	using query = tuple<int, int, int>; // end index, max value, query index
	vector<int> leftmostBuildingQueries(vector<int> &heights, vector<vector<int>> &queries)
	{
		const int N = heights.size();
		const int M = queries.size();

		// query processing
		priority_queue<query, vector<query>, less<query>> pq;
		for (int qIdx = 0; qIdx < M; ++qIdx)
		{
			const int aIdx = queries[qIdx][0];
			const int bIdx = queries[qIdx][1];
			pq.push(make_tuple(max(aIdx, bIdx), max(heights[aIdx], heights[bIdx]), qIdx));
		}

		// traverse array, handle query
		vector<int> result(M);
		SegTree<int, MININT> closestPos(50000, N);
		closestPos.Init();
		for (int i = N - 1; i >= 0; --i)
		{
			// update
			closestPos.Update(heights[i], i);
			if (!pq.empty())
			{
				const auto [eIdx, tgtVal, qIdx] = pq.top();
				if (eIdx != i)
					break;
				pq.pop();
				// search query, lowerbound
				result[qIdx] = closestPos.Query(tgtVal, 50000);
				if (result[qIdx] == N)
					result[qIdx] = -1;
			}
		}
		return result;
	}
};
auto _ = []()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	return 0;
}();
//

// test
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;
}
