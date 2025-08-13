
/*
	BOJ 12899

	각 원소의 frequency를 저장하는 segtree를 운영한다.
	누적합을 통하면 누가 k번째 원소인지 쉽게 알 수 있다.

	흥미로운 부분은 세먼먼트 트리를 root에서 시작하여 탐색하며 내려올 수 있다는 부분.
*/
#include <iostream>
#include <array>

using ll = long long;

int constexpr log2(int n)
{
	int result = 0;
	while (n > (1 << result))
		++result;
	return result;
}

int constexpr const MAX = 2000000;
int constexpr const lg2n = log2(MAX);
int constexpr const offset = 1 << lg2n;
std::array<ll, offset + MAX> sg;	// constexpr로 초기화 한 segment tree

void point_update(int node, int val) {
	--node |= offset;	// starts from leaf
	while (node)
	{
		sg[node] += val;
		node >>= 1;
	}
};
int find_kth_elem(int k) {	// in logN
	// starts from root
	int node = 1;
	if (k > sg[1])
	{
		return -1;
	}
	while (node < offset)
	{
		// pick left or right
		int const l = node << 1;
		int const r = l + 1;
		if (k > sg[l])
		{
			// to the right
			k -= sg[l];
			node = r;
		}
		else
		{
			// to the left
			node = l;
		}
	}
	node -= offset - 1;
	point_update(node, -1);
	return node;	// 1 indexed
};

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// init seg tree
	std::fill(sg.begin(), sg.end(), 0);

	// input
	int N, T, X;
	std::cin >> N;
	while (N--)
	{
		std::cin >> T >> X;
		if (T & 1)	// 1
		{
			point_update(X, 1);
		}
		else	// 2
		{
			std::cout << find_kth_elem(X) << '\n';
		}
	}
}
