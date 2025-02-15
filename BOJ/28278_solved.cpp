
#include <iostream>
#include <stack>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::stack<int> st;
	int N, ops, num;
	std::cin >> N;
	while (N--)
	{
		std::cin >> ops;
		if (ops == 1)
		{
			std::cin >> num;
			st.push(num);
		}
		else if (ops == 2)
		{
			if (st.empty())
			{
				std::cout << "-1\n";
			}
			else
			{
				std::cout << st.top() << '\n';
				st.pop();
			}
		}
		else if (ops == 3)
		{
			std::cout << st.size() << '\n';
		}
		else if (ops == 4)
		{
			std::cout << st.empty() << '\n';
		}
		else if (ops == 5)
		{
			if (st.empty())
			{
				std::cout << "-1\n";
			}
			else
			{
				std::cout << st.top() << '\n';
			}
		}
	}
}