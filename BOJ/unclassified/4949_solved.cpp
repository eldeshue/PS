
#include <iostream>
#include <limits>
#include <string>
#include <stack>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	while (true)
	{
		std::string input;
		std::stack<char> st;
		bool result = true;
		std::getline(std::cin, input, '.');
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	// ignore left '\n'
		if (input.empty() || input[0] == '\n')
			break;
		for (const char &c : input)
		{
			if (c == '(' || c == '[')
			{
				st.push(c);
			}
			else if (c == ')' || c == ']')
			{
				if (!st.empty()
					&& ((st.top() == '(' && c == ')')
					|| (st.top() == '[' && c == ']')))	// match
				{
					st.pop();
				}
				else
				{
					result = false;
					break;
				}
			}
		}
		if (result && st.empty())
			std::cout << "yes\n";
		else
			std::cout << "no\n";
	}
}