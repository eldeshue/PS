/*
	BOJ 1168

	과거 풀었던 요세푸스 문제를 segment tree로 최적화.
	기존의 요세푸스는 N * K로 쉽게 풀 수 있었음.
	그러나, 이 문제에서는 시간 문제로 통과할 수 없음.

	========================================

	12899번에서 K번째 원소를 세그먼트 트리로 쉽게 구하는 것을 이용,
	k번째 원소를 찾은 후, 이를 제거하는 동작을 응용하여 요제푸스를 구현함.

	한 원소를 제거할 때 마다 O(log N)의 비용이 들어감
	따라서 최종 비용은 O(N log N)임.
*/
#include <array>
#include <iostream>

using ll = long long;

int constexpr log2(int n)
{
	int result = 0;
	while (n > (1 << result))
		++result;
	return result;
}

int constexpr const MAX = 100000;
int constexpr const lg2n = log2(MAX);
int constexpr const offset = 1 << lg2n;
std::array<ll, offset + MAX> sg;	// 0 based index

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
	int N, K;
	std::cin >> N >> K;

	// set nums
	for (int i = 1; i <= N; ++i)
		sg[(i - 1) | offset] = 1;
	for (int i = offset + MAX - 1; i >= 1; --i)
		sg[i >> 1] += sg[i];

	// print
	int pos = 0;
	std::cout << '<';
	while (true)
	{
		pos += K - 1;
		pos %= N;
		std::cout << find_kth_elem(pos + 1);
		if (--N == 0)
			break;
		std::cout << ", ";
	}
	std::cout << '>';
}