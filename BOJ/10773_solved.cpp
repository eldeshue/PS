
#include <iostream>
#include <stack>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	std::stack<int> numbers;

	int K, n;
	std::cin >> K;
	for (int i = 0; i < K; ++i)
	{
		std::cin >> n;
		if (n == 0)
		{
			numbers.pop();
		}
		else
		{
			numbers.push(n);
		}
	}
	int result = 0;
	while (!numbers.empty())
	{
		result += numbers.top();
		numbers.pop();
	}
	std::cout << result;
}