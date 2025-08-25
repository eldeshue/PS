/*
	BOJ 16978
*/
#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>

using ll = long long;
using Q1 = std::pair<int, ll>;
using Q2 = std::tuple<int, int, int, int>;

int log2(int const n)
{
	int result = 0;
	while (n > (1 << result))
		result++;
	return result;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// build segtree
	// 1 base
	int N;
	std::cin >> N;
	int const depth = log2(N);
	int const offset = (1 << depth);
	std::vector<ll> sgtree(2 * offset, 0);
	for (int i = 0; i < N; ++i)
		std::cin >> sgtree[offset | i];
	for (int i = sgtree.size() - 1; i > 1; --i)	// init tree
		sgtree[i >> 1] += sgtree[i];

	// 1 base
	auto point_update = [&](int pos, ll new_val) {
		pos = --pos | offset;
		ll const diff = new_val - sgtree[pos];
		while (pos >= 1)
		{
			sgtree[pos] += diff;
			pos >>= 1;
		}
		};
	auto range_sum = [&](int l, int r) -> ll {
		ll sum = 0;
		l = --l | offset; r = --r | offset;	// both inclusive
		while (l <= r)
		{
			if (l & 1)
				sum += sgtree[l++];
			if (~r & 1)
				sum += sgtree[r--];
			l >>= 1;
			r >>= 1;
		}
		return sum;
		};

	// input queries
	int M;
	std::cin >> M;
	std::deque<Q1> q1;
	std::deque<Q2> q2;
	int q2_cnt = 0;
	for (int i = 0; i < M; ++i)
	{
		char q_type;
		std::cin >> q_type;
		if (q_type & 1)	// type 1
		{
			// update
			int pos, val;
			std::cin >> pos >> val;
			q1.push_back(Q1(pos, val));
		}
		else
		{
			// sum query
			int k, l, r;
			std::cin >> k >> l >> r;
			q2.push_back(Q2(k, l, r, q2_cnt++));
		}
	}

	// sort query 2
	std::sort(q2.begin(), q2.end(), std::less<Q2>());

	// handle query
	std::vector<ll> result(q2.size(), 0);
	int update_cnt = 0;
	while (!q2.empty())
	{
		auto const [k, l, r, pos] = q2.front();
		q2.pop_front();

		while (update_cnt < k && !q1.empty())
		{
			auto [i, v] = q1.front();
			q1.pop_front();
			point_update(i, v);
			++update_cnt;
		}
		result[pos] = range_sum(l, r);
	}

	// print result
	for (auto const r : result)
		std::cout << r << '\n';
}