
/*
	그리디 알고리즘

	처음에는 dp를 고민했으나, 메모리가 부족하리라 여겨서 fail
	이후에는 정렬하고 데이터를 merge하여 값을 찾으려 시도했으나, 이 또한 메모리가 과도하게 소모하는 부분이 있어서 실패.

	이후 다른 사람의 풀이를 봤는데, 누적합에 대한 수학적 직관을 이용하는 문제였음.

	풀이 자체는 대단히 간단함.
*/
#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, sum = 1; // 시작하는 값을 1로 줘야지 sum과 같은 값에 대해서 문제가 없음
	std::cin >> N;
	std::vector<int> nums(N);
	for (int i = 0; i < N; ++i)
		std::cin >> nums[i];
	std::sort(nums.begin(), nums.end(), std::less<int>());
	for (const int &n : nums)
	{
		if (sum < n) // 지금까지의 누적합과 비교하여, 새롭게 추가되는 값이 더 크면 무조건 gap이 발생함
		{
			break;
		}
		sum += n;
	}
	std::cout << sum;
	return 0;
}
