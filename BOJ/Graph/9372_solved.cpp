
#include <iostream>
#include <numeric>
#include <queue>
#include <stack>
#include <vector>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	using pii = std::pair<int, int>;

	int T;
	std::cin >> T;
	while (T--)
	{
		int N, M;
		std::cin >> N >> M;
		for (int i = 0; i < M; ++i)
		{
			int a, b;
			std::cin >> a >> b;
		}
		std::cout << N - 1 << '\n';	// 단일 연결 요소여야 하므로....
	}
}