
#include <iostream>
#include <string>
#include <stack>
#include <vector>

bool is_VPS(const std::string& str)
{
	std::stack<char> st;
	for (const auto& c : str)
	{
		if (c == '(')
		{
			st.push(c);
		}
		else
		{
			if (st.empty()) // SEGV ´ëºñ
			{
				st.push(')');
				break;
			}
			st.pop();
		}
	}

	if (st.empty())
	{
		return true;
	}
	else
	{
		return false;
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::string input_str;
	std::vector<bool> result;
	int N;
	std::cin >> N;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> input_str;
		result.push_back(is_VPS(input_str));
	}

	for (const auto& elem : result)
	{
		std::cout << ( elem ? "YES\n" : "NO\n");
	}
}