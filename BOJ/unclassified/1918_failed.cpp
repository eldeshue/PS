#include <iostream>
#include <stack>
#include <string>

std::string result;

void parse()
{
	std::stack<char> oprt;
	oprt.push('(');
	char input;
	while (true)
	{
		std::cin >> input;
		if (input == '*' || input == '/')
		{
			oprt.push(input);
		}
		else if (input == '+' || input == '-')
		{
			if (oprt.top() == '*' || oprt.top() == '/')
			{
				while (oprt.top() != '(')
				{
					result.push_back(oprt.top());
					oprt.pop();
				}
				oprt.push(input);
			}
			else
			{
				oprt.push(input);
			}
		}
		else if (input == '(')
		{
			oprt.push(input);
		}
		else if (input == ')')
		{
			while (oprt.top() != '(')
			{
				result.push_back(oprt.top());
				oprt.pop();
			}
			oprt.pop();
		}
		else if (input == '0')// EOF)
		{
			while (oprt.top() != '(')
			{
				result.push_back(oprt.top());
				oprt.pop();
			}
			oprt.pop();
			return;
		}
		else
		{
			result.push_back(input);
		}
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	parse();
	std::cout << result;
}

