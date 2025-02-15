
#include <iostream>
#include <vector>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, M;
	std::cin >> N >> M;
	std::vector<int> nums(N);
	for (int i = 0; i < N; ++i)
	{
		std::cin >> nums[i];
	}
	// two pointer
	int cnt = 0, sum = 0, fast = 0, slow = 0;
	while (fast < N)
	{
		sum += nums[fast];
		while (sum >= M)
		{
			if (sum == M)
			{
				cnt++;
			}
			sum -= nums[slow];
			slow++;
		}
		fast++;
	}
	std::cout << cnt;
}