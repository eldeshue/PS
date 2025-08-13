
/*
	BOJ 16975

	세그먼트 트리 + 차분 배열 테크닉

	==========================

	range update로 K를 해주고,
	point query가 들어오면, root를 향해서 parent node에 누적된 update를 반영함.
*/
#include <iostream>
#include <vector>

using ll = long long;

int log2(int n)
{
	int result = 0;
	while (n > (1 << result))
		++result;
	return result;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input, init seg tree
	int N;
	std::cin >> N;
	int const lg2n = log2(N);
	int const offset = 1 << lg2n;
	std::vector<ll> sg(offset + N, 0);	// 0 based index
	for (int i = 0; i < N; ++i)
		std::cin >> sg[offset + i];

	// seg tree
	auto collect_sg = [&](int node) {
		ll sum = 0;
		--node |= offset;
		while (node)
		{
			sum += sg[node];
			node >>= 1;
		}
		return sum;
		};
	auto update_sg = [&](int l, int r, ll k) {
		for (--l |= offset, --r |= offset; l <= r; l >>= 1, r >>= 1)
		{
			// left, odd
			if (l & 1)
				sg[l++] += k;
			// right, even
			if (~r & 1)
				sg[r--] += k;
		}
		};

	// query
	int M;
	std::cin >> M;
	while (M--)
	{
		int t, a, b, k;
		std::cin >> t;
		if (1 & t)
		{
			// update
			std::cin >> a >> b >> k;
			update_sg(a, b, k);
		}
		else
		{
			// print
			std::cin >> a;
			std::cout << collect_sg(a) << '\n';
		}
	}
}
