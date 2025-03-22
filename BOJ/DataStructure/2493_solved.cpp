
#include <iostream>
#include <stack>

int main()
{
	std::ios_base::sync_with_stdio();
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	using pii = std::pair<int, int>;

	// use lower bound
	int N;
	std::cin >> N;
	std::stack<pii> monoton_stack;
	for (int i = 1; i <= N; ++i)
	{
		int val;
		std::cin >> val;

		// value보다 큰 놈들 중, index가 가장 큰 녀석을 찾아야 함
		while (!monoton_stack.empty() && monoton_stack.top().first < val)
		{
			monoton_stack.pop();
		}

		// print
		if (monoton_stack.empty())
		{
			// not found
			std::cout << "0 ";
		}
		else
		{
			std::cout << monoton_stack.top().second << ' ';
		}

		// save
		monoton_stack.push(std::make_pair(val, i));
	}
}