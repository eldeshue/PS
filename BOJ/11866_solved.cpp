
#include <iostream>
#include <queue>

void josepus(std::queue<int>& Q, const int& k)
{
	std::cout << '<';
	while (Q.size() > 1)
	{
		for (int i = 1; i < k; ++i)
		{
			Q.push(Q.front());
			Q.pop();
		}
		std::cout << Q.front() << ',' << ' ';
		Q.pop();
	}
	std::cout << Q.front() << '>';
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::queue<int> Q;
	int N, K;
	std::cin >> N >> K;
	for (int i = 1; i <= N; ++i)
	{
		Q.push(i);
	}
	josepus(Q, K);
}