
#include <iostream>
#include <vector>

/*
	Kadane's algorithm

	나의 풀이는 two pointer에서 시작함. 
	두 개의 포인터를 substring의 시작과 끝을 가리킴.

	누적합이 양수인 동안 오른쪽 포인터를 전진시킴.
	누적합이 음수가 되는 순간, 두 포인터를 현재 위치 다음으로 옯김.

	즉 지금까지 얻은 누적합이 최대 누적합에 도움이 안되면, 이를 버리는 것.
	누적합이 도움이 되는 동안에는 유지하고, 그렇지 않으면 버린다.
	
	누적합이 감소하는 한이 있더라도, 양수라면 최대 누적합의 일부가 될 가능성이 있음.
	하지만, 누적합이 음수가 되는 순간, 기존의 누적합을 유지하는 것이 손해가 됨.

	나는 이렇게 투 포인터에서 생각을 발전시켰는데, 
	사실은 Kadane's algorithm이라는 유명한 테크닉이었음. dp의 최적화.
*/

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, num, maxSum = -2e9, curSum = 0;
	std::cin >> N;
	for (int i = 0; i < N; ++i)				// O(N)
	{
		std::cin >> num;
		curSum += num;						// 합을 누적
		maxSum = std::max(maxSum, curSum);	// 최댓값 업데이트
		if (curSum < 0)						// 기존의 누적 합을 버림.
			curSum = 0;
	}
	std::cout << maxSum;
}