/*
	using deque, greedy

	keep deque ascending order.
*/
#include <iostream>
#include <string>

using namespace std;

// solution
#pragma GCC optimize("03")
#pragma GCC target ("avx")

#include <deque>

class Solution
{
public:
	string removeKdigits(string num, int k)
	{
		deque<char> save;
		string result;

        // key idea, keep deque ascending order.
		for (int i = 0; i < num.size(); ++i)
		{
            // if save is empty, just push back
			if (save.empty())
			{
				save.push_back(num[i]);
				continue;
			}
            // keep save ascending order
			while (k > 0 && !save.empty() && save.back() > num[i])
			{
                k--;
				save.pop_back();
			}
			save.push_back(num[i]);
		}
        // erase left over
        while (k > 0)
        {
            k--;
            save.pop_back();
        }
        // erase leading zero
        while (!save.empty() && save.front() == '0')
        {
            save.pop_front();
        }
        // set result
		for (int i = 0; i < save.size(); ++i)
		{
			result.push_back(save[i]);
		}
        // if result is empty
        if (result.empty())
            result = "0";
		return result;
	}
};

// solution

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;

}
