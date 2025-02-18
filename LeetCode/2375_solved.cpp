#include <iostream>
#include <vector>

using namespace std;

#include <stack>
class Solution {
private:
public:
	string smallestNumber(string pattern) {
		std::stack<char> st;
		std::string result;
		char c = '1';
		for (const char p : pattern)
		{
			if (p == 'D')
			{
				// decreasing
				st.push(c++);
			}
			else
			{
				// increasing
				result.push_back(c++);
				while (!st.empty())
				{
					result.push_back(st.top());
					st.pop();
				}
			}
		}
		result.push_back(c);
		while (!st.empty())
		{
			result.push_back(st.top());
			st.pop();
		}

		return result;
	}
};