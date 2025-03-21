
/*
	boj 11399, ATM

	줄을 서는 순서에 따라서 인원의 대기시간 총 합이 달라진다.
	앞에 서는 사람의 대기시간이 보다 많이 누적되므로,
	대기시간순으로 오름차순 정렬하고, 이를 계산함이 옳다.
*/

#include <iostream>
#include <algorithm>
#include <array>

std::array<int, 1000> waitTime;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	std::cin >> N;
	for (int i = 0; i < N; ++i)
		std::cin >> waitTime[i];
	std::sort(waitTime.begin(), waitTime.begin() + N);
	int result = 0;
	for (int i = 0; i < N; ++i)
	{
		result += waitTime[i] * (N - i);
	}
	std::cout << result;
}
