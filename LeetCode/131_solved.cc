
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// solution
#pragma GCC optimize("03")
#pragma GCC target ("avx")
#include <deque>

class Solution
{
private:
	deque<string> curPart;
	bool isPelin(const string& s)
	{
		int slow = 0, fast = s.size() - 1;
		while (slow < fast)
		{
			if (s[slow] != s[fast])
				return false;
			slow++; fast--;
		}
		return true;
	}
	void backTrack(const string& s, const int& idx,
		vector<vector<string>>& result)
	{
		// base case, copy and push the result
		if (isPelin(curPart.back()))
		{
			if (idx == s.size())
			{
				result.push_back(vector<string>(curPart.size()));
				for (int i = 0; i < curPart.size(); ++i)
				{
					result.back()[i] = curPart[i];
				}
			}
			else	// push back or start new pelin
			{
				//
				curPart.push_back(string(1, s[idx]));
				backTrack(s, idx + 1, result);
				curPart.pop_back();
				//
				curPart.back().push_back(s[idx]);
				backTrack(s, idx + 1, result);
				curPart.back().pop_back();
			}
		}
		else if (idx < s.size())	// not pelindrome
		{
				curPart.back().push_back(s[idx]);
				backTrack(s, idx + 1, result);
				curPart.back().pop_back();
		}
	}
public:
	vector<vector<string>> partition(string s)
	{
		vector<vector<string>> result;
		curPart.push_back(string(1, s[0]));
		backTrack(s, 1, result);
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
