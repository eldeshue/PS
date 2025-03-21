
#include <iostream>
#include <queue>
#include <vector>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	std::priority_queue<int, std::vector<int>, std::greater<int>> PQ;

	int N, card1, card2, sum, result = 0;
	std::cin >> N;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> card1;
		PQ.push(card1);
	}
	while (PQ.size() > 1)
	{
		card1 = PQ.top();
		PQ.pop();
		card2 = PQ.top();
		PQ.pop();
		sum = card1 + card2;
		result += sum;
		PQ.push(sum);
	}
	std::cout << result;
}
