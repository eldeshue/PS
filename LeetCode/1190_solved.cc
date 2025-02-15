#include <string>

using namespace std;

#include <deque>
class Solution
{
public:
	string reverseParentheses(string s)
	{
		deque<char> q;
		deque<char> st;
		string result;
		for (const char &c : s)
		{
			if (c == ')')
			{
				while (st.back() != '(')
				{
					q.push_back(st.back());
					st.pop_back();
				}
				st.pop_back();
				while (!q.empty())
				{
					st.push_back(q.front());
					q.pop_front();
				}
			}
			else
			{
				st.push_back(c);
			}
		}
		for (const char &c : st)
		{
			result.push_back(c);
		}
		return result;
	}
};
