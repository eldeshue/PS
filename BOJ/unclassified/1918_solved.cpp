
#include <iostream>
#include <string>
#include <stack>

std::stack<char> oprt_stack;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::string input;
	std::cin >> input;
	for (int i = 0; i < input.size(); ++i)
	{
		char& cur_char = input[i];
		if ('A' <= cur_char && cur_char <= 'Z')	// char
		{
			std::cout << cur_char;
		}
		else if (cur_char == '(')	// bracket
		{
			oprt_stack.push(cur_char);
		}
		else if (cur_char == ')')
		{
			while (oprt_stack.top() != '(')
			{
				std::cout << oprt_stack.top();
				oprt_stack.pop();
			}
			oprt_stack.pop();
		}
		else	// operator
		{
			// 동일 우선순위 사이에서는 선입 선출이 필요함.
			if (cur_char == '+' || cur_char == '-')
			{
				while (!oprt_stack.empty() && oprt_stack.top() != '(')
				{
					std::cout << oprt_stack.top();
					oprt_stack.pop();
				}
				oprt_stack.push(cur_char);
			}
			else if (cur_char == '*' || cur_char == '/')	// *, /가 우선순위가 높으므로, + - 위에 와야 함.
			{
				while (!oprt_stack.empty() && (oprt_stack.top() == '*' || oprt_stack.top() == '/'))
				{
					std::cout << oprt_stack.top();
					oprt_stack.pop();
				}
				oprt_stack.push(cur_char);
			}
		}
	}
	while (!oprt_stack.empty())
	{
		std::cout << oprt_stack.top();
		oprt_stack.pop();
	}
}