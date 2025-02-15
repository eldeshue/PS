
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	int N, K;
	std::cin >> N >> K;
	std::vector<int> buffer(N);
	for (auto& n : buffer)
		std::cin >> n;

	// calculate
	int pushCnt = 0;
	int result = -1;
	std::function<void(int, int)> recurse = [&](int left, int right) {
		if (left == right)
			return;
		int const mid = (left + right) >> 1;
		// left
		recurse(left, mid);
		// right
		recurse(mid + 1, right);
		// merge
		int const nextPushCnt = pushCnt + right - left + 1;
		if (pushCnt < K && K <= nextPushCnt)
		{
			// result found
			int gap = K - pushCnt;
			// sort
			std::sort(buffer.begin() + left, buffer.begin() + right + 1);
			result = buffer[left + gap - 1];
		}
		pushCnt = nextPushCnt;
		};
	recurse(0, N - 1);
	std::cout << result;
}