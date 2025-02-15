
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
			// ���� �켱���� ���̿����� ���� ������ �ʿ���.
			if (cur_char == '+' || cur_char == '-')
			{
				while (!oprt_stack.empty() && oprt_stack.top() != '(')
				{
					std::cout << oprt_stack.top();
					oprt_stack.pop();
				}
				oprt_stack.push(cur_char);
			}
			else if (cur_char == '*' || cur_char == '/')	// *, /�� �켱������ �����Ƿ�, + - ���� �;� ��.
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