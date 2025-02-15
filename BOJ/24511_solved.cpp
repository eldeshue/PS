
#include <deque>
#include <iostream>
#include <vector>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::deque<int> q;
	int N, input;
	std::cin >> N;
	std::vector<int> isStack(N);
	for (int i = 0; i < N; ++i)
	{
		std::cin >> isStack[i];
	}
	for (int i = 0; i < N; ++i)
	{
		std::cin >> input;
		if (!isStack[i])
		{
			q.push_back(input);
		}
	}
	std::cin >> N;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> input;
		q.push_front(input);
		std::cout << q.back() << ' ';
		q.pop_back();
	}
}